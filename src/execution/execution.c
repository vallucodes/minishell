#include "../../inc/minishell.h"
#include <sys/wait.h>

/* DOCUMENTATION
1. Start at the root (topmost PIPE node)
2. Always run the command on .next_left. That can include redir or builtins
3. After executing .next_left, we:
		node = node->next_right;
		that means we teleport to the next PIPE node
4. Repeat until node == NULL - end of pipeline

EXAMPLE!
        PIPE 1
       /    \
   cat      PIPE 2
           /    \
      grep       wc

1. node = PIPE 1
   → node->next_left = cat
   → Run cat, setup stdout to pipe1[1]
   → Close pipe1[1] in parent
   → Move to: node = node->next_right → PIPE 2

2. node = PIPE 2
   → node->next_left = grep
   → Run grep, setup stdin = pipe1[0], stdout = pipe2[1]
   → Close pipe1[0], pipe2[1] in parent
   → Move to: node = node->next_right → wc

3. node = wc (this is just the last command in .next_left of the final pipe)
   → Run wc, setup stdin = pipe2[0], stdout = STDOUT_FILENO
   → Close pipe2[0] in parent
   → Done!
-------------------------------------------------------------------------------
*/

static int is_builtin(const char *cmd)
{
	if (!cmd)
		return (0);
	return (ft_strcmp(cmd, "echo") == 0 ||
			ft_strcmp(cmd, "cd") == 0 ||
			ft_strcmp(cmd, "pwd") == 0 ||
			ft_strcmp(cmd, "export") == 0 ||
			ft_strcmp(cmd, "unset") == 0 ||
			ft_strcmp(cmd, "env") == 0 ||
			ft_strcmp(cmd, "exit") == 0);
}

static void close_unused_fds(t_execution *exec, int has_pipe)
{
	if (exec->fd[FD_IN] != STDIN_FILENO)
		close(exec->fd[FD_IN]);
	if (exec->fd[FD_OUT] != STDOUT_FILENO)
		close(exec->fd[FD_OUT]);
	if (exec->prev_fd != STDIN_FILENO)
		close(exec->prev_fd);
	if (has_pipe)
	{
		close(exec->pipefd[0]);
		close(exec->pipefd[1]);
	}
}

static void parse_redirections_and_command(t_ast *node, t_execution *exec)
{
	while (node)
	{
		if (node->type == REDIRECT_IN || node->type == HERE_STRING)
			exec->fd[FD_IN] = safe_open_redirect(node->file, O_RDONLY, 0);
		else if (node->type == REDIRECT_OUT)
			exec->fd[FD_OUT] = safe_open_redirect(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (node->type == REDIRECT_APPEND)
			exec->fd[FD_OUT] = safe_open_redirect(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (node->type == COMMAND)
			exec->cmd_args = node->cmd;
		node = node->next_left;
	}
}

static void handle_first_child(t_minishell *mshell, t_execution *exec)
{
	if (exec->fd[FD_OUT] != STDOUT_FILENO)
		dup2(exec->fd[FD_OUT], STDOUT_FILENO);
	else
		dup2(exec->pipefd[1], STDOUT_FILENO);

	if (exec->fd[FD_IN] != STDIN_FILENO)
		dup2(exec->fd[FD_IN], STDIN_FILENO);

	close_unused_fds(exec, 1); // 1 = has pipe

	if (is_builtin(exec->cmd_args[0]))
		exit(execute_builtin(mshell, exec->cmd_args));
	execve(exec->cmd_args[0], exec->cmd_args, mshell->envp->envp);
	perror(exec->cmd_args[0]);
	exit(1);
}

static void handle_middle_child(t_minishell *mshell, t_execution *exec)
{
	if (exec->fd[FD_IN] != STDIN_FILENO)
		dup2(exec->fd[FD_IN], STDIN_FILENO);
	else
		dup2(exec->prev_fd, STDIN_FILENO);

	if (exec->fd[FD_OUT] != STDOUT_FILENO)
		dup2(exec->fd[FD_OUT], STDOUT_FILENO);
	else
		dup2(exec->pipefd[1], STDOUT_FILENO);

	close_unused_fds(exec, 1);

	if (is_builtin(exec->cmd_args[0]))
		exit(execute_builtin(mshell, exec->cmd_args));
	execve(exec->cmd_args[0], exec->cmd_args, mshell->envp->envp);
	perror(exec->cmd_args[0]);
	exit(1);
}

static void handle_last_child(t_minishell *mshell, t_execution *exec)
{
	if (exec->fd[FD_IN] != STDIN_FILENO)
		dup2(exec->fd[FD_IN], STDIN_FILENO);
	else
		dup2(exec->prev_fd, STDIN_FILENO);

	if (exec->fd[FD_OUT] != STDOUT_FILENO)
		dup2(exec->fd[FD_OUT], STDOUT_FILENO);

	close_unused_fds(exec, 0); // 0 = no pipe

	if (is_builtin(exec->cmd_args[0]))
		exit(execute_builtin(mshell, exec->cmd_args));
	execve(exec->cmd_args[0], exec->cmd_args, mshell->envp->envp);
	perror(exec->cmd_args[0]);
	exit(1);
}

void execute_ast(t_minishell *mshell, t_ast *ast)
{
	t_execution exec;
	pid_t pid;
	int i = 0;

	ft_bzero(&exec, sizeof(exec));
	exec.prev_fd = STDIN_FILENO;



	while (ast)
	{
		exec.has_next_pipe = (ast->next_right != NULL);
		exec.cmd_args = NULL;
		exec.fd[FD_IN] = STDIN_FILENO;
		exec.fd[FD_OUT] = STDOUT_FILENO;

		parse_redirections_and_command(ast, &exec); // fill exec.cmd_args, fd[0/1], etc.
		if (is_builtin(exec.cmd_args[0]) && !exec.has_next_pipe)
		{
			execute_builtin(mshell, exec.cmd_args);
			ast = ast->next_right;
		}
		if (!exec.cmd_args || !exec.cmd_args[0])
		{
			ast = ast->next_right;
			continue;
		}

		if (exec.has_next_pipe && pipe(exec.pipefd) < 0)
		{
			perror("pipe");
			return;
		}

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return;
		}
		if (pid == 0)
		{
			if (i == 0)
				handle_first_child(mshell, &exec);
			else if (!exec.has_next_pipe)
				handle_last_child(mshell, &exec);
			else
				handle_middle_child(mshell, &exec);
		}

		// Parent cleanup
		close(exec.prev_fd);
		exec.prev_fd = exec.pipefd[0]; // pass read-end to next command
		close(exec.pipefd[1]);

		i++;
		ast = ast->next_right;
	}

	while (wait(NULL) > 0) {} // Wait for all children
}

