#include "../../inc/minishell.h"
#include <sys/wait.h>


static int	is_builtin(const char *cmd)
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

static void handle_redirections(t_ast *node, t_execution *exec)
{
	while (node)
	{
		if (node->type == REDIRECT_IN || node->type == HERE_DOCUMENT)
			exec->temp_fd[FD_IN] = safe_open_redirect(node->file, O_RDONLY, 0);
		else if (node->type == REDIRECT_OUT)
			exec->temp_fd[FD_OUT] = safe_open_redirect(node->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (node->type == REDIRECT_APPEND)
			exec->temp_fd[FD_OUT] = safe_open_redirect(node->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		node = node->next_left;
	}
}

static t_ast *get_cmd_node(t_ast *node, char ***cmd_args)
{
	t_ast *cmd_node = NULL;
	while (node)
	{
		if (node->type == COMMAND)
		{
			*cmd_args = node->cmd;
			cmd_node = node;
		}
		node = node->next_left;
	}
	return (cmd_node);
}

static int fork_redirection_only(t_minishell *mshell, t_execution *exec)
{
	pid_t pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0)
	{
		if (exec->temp_fd[FD_IN] != STDIN_FILENO)
			dup2(exec->temp_fd[FD_IN], STDIN_FILENO);
		if (exec->temp_fd[FD_OUT] != STDOUT_FILENO)
			dup2(exec->temp_fd[FD_OUT], STDOUT_FILENO);
		close(exec->temp_fd[FD_IN]);
		close(exec->temp_fd[FD_OUT]);
		exit(0);
	}
	mshell->command_count++;
	mshell->last_pid = pid;
	if (exec->temp_fd[FD_IN] != STDIN_FILENO)
		close(exec->temp_fd[FD_IN]);
	if (exec->temp_fd[FD_OUT] != STDOUT_FILENO)
		close(exec->temp_fd[FD_OUT]);
	return (1);
}

//maybe can stat wutg this tmrr 11.4, add them to struct!
static void setup_child_fds(int prev_fd, int *pipefd, int has_next_pipe, t_execution *exec)
{
	if (exec->temp_fd[FD_IN] != STDIN_FILENO)
		dup2(exec->temp_fd[FD_IN], STDIN_FILENO);
	else if (prev_fd != STDIN_FILENO)
		dup2(prev_fd, STDIN_FILENO);

	if (exec->temp_fd[FD_OUT] != STDOUT_FILENO)
		dup2(exec->temp_fd[FD_OUT], STDOUT_FILENO);
	else if (has_next_pipe)
		dup2(pipefd[1], STDOUT_FILENO);

	if (exec->temp_fd[FD_IN] != STDIN_FILENO)
		close(exec->temp_fd[FD_IN]);
	if (exec->temp_fd[FD_OUT] != STDOUT_FILENO)
		close(exec->temp_fd[FD_OUT]);
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	if (has_next_pipe)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

int	wait_for_children(t_minishell *mshell)
{
	int i = 0, wstatus, exit_code = 0;
	while (i < mshell->command_count)
	{
		if (mshell->last_pid == wait(&wstatus))
			exit_code = WEXITSTATUS(wstatus);
		i++;
	}
	return exit_code;
}


static void	redirect_and_restore_builtin(t_execution *exec,
				t_minishell *mshell, char **cmd_args)
{
	int original_stdin = -1;
	int original_stdout = -1;

	if (exec->temp_fd[FD_IN] != STDIN_FILENO)
	{
		original_stdin = dup(STDIN_FILENO);
		dup2(exec->temp_fd[FD_IN], STDIN_FILENO);
		close(exec->temp_fd[FD_IN]);
	}
	if (exec->temp_fd[FD_OUT] != STDOUT_FILENO)
	{
		original_stdout = dup(STDOUT_FILENO);
		dup2(exec->temp_fd[FD_OUT], STDOUT_FILENO);
		close(exec->temp_fd[FD_OUT]);
	}
	execute_builtin(mshell, cmd_args);
	if (original_stdout != -1)
	{
		dup2(original_stdout, STDOUT_FILENO);
		close(original_stdout);
	}
	if (original_stdin != -1)
	{
		dup2(original_stdin, STDIN_FILENO);
		close(original_stdin);
	}
}

void execute_ast(t_minishell *mshell, t_ast *ast)
{
	t_ast *cmd_node;
	t_execution exec;
	int pipefd[2], prev_fd = STDIN_FILENO, has_next_pipe;
	pid_t pid;
	char **external_cmd;

	while (ast)
	{
		exec.temp_fd[FD_IN] = STDIN_FILENO;
		exec.temp_fd[FD_OUT] = STDOUT_FILENO;
		exec.cmd_args = NULL;
		cmd_node = NULL;
		has_next_pipe = (ast->next_right != NULL);

		if (has_next_pipe && pipe(pipefd) < 0)
		{
			perror("pipe");
			return;
		}

		handle_redirections(ast, &exec);
		cmd_node = get_cmd_node(ast, &exec.cmd_args);

		//if only redirection is here like  < Makefile >out23
		if ((!exec.cmd_args || !exec.cmd_args[0]) &&
			(exec.temp_fd[FD_IN] != STDIN_FILENO || exec.temp_fd[FD_OUT] != STDOUT_FILENO))
		{
			if (fork_redirection_only(mshell, &exec) < 0)
				return;
			ast = ast->next_right;
			continue;
		}
		else if (!exec.cmd_args || !exec.cmd_args[0])
		{
			ast = ast->next_right;
			continue;
		}

		if (is_builtin(exec.cmd_args[0]) && !has_next_pipe)
		{
			redirect_and_restore_builtin(&exec, mshell, exec.cmd_args);
			ast = ast->next_right;
			continue;
		}

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return;
		}

		if (pid == 0)
		{
			setup_child_fds(prev_fd, pipefd, has_next_pipe, &exec);
			if (is_builtin(exec.cmd_args[0]))
			{
				execute_builtin(mshell, exec.cmd_args);
				delete_minishell(mshell);
				exit(mshell->exitcode);
			}
			if (!cmd_node)
			{
				ft_dprintf(2, "minishell: command node not found\n");
				exit(127);
			}
			external_cmd = get_command_argv(mshell, cmd_node);
			execve(external_cmd[0], exec.cmd_args, mshell->envp->envp);
			perror(external_cmd[0]);
			ft_free_2d(external_cmd);
			arena_destroy(&mshell->arena);
			exit(127);
		}
		else
		{
			mshell->command_count++;
			mshell->last_pid = pid;
			if (prev_fd != STDIN_FILENO)
				close(prev_fd);
			if (exec.temp_fd[FD_IN] != STDIN_FILENO)
				close(exec.temp_fd[FD_IN]);
			if (exec.temp_fd[FD_OUT] != STDOUT_FILENO)
				close(exec.temp_fd[FD_OUT]);
			if (has_next_pipe)
			{
				close(pipefd[1]);
				prev_fd = pipefd[0];
			}
		}
		ast = ast->next_right;
	}
	mshell->exitcode = wait_for_children(mshell);
}
