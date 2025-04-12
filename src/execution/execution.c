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



static t_ast *get_cmd_node(t_ast *ast)
{
	while (ast)
	{
		if (ast->type == COMMAND)
			return (ast);
		ast = ast->next_left;
	}
	return (NULL);
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
		if (exec->redir_fd[FD_IN] != STDIN_FILENO)
			dup2(exec->redir_fd[FD_IN], STDIN_FILENO);
		if (exec->redir_fd[FD_OUT] != STDOUT_FILENO)
			dup2(exec->redir_fd[FD_OUT], STDOUT_FILENO);
		close(exec->redir_fd[FD_IN]);
		close(exec->redir_fd[FD_OUT]);
		exit(0);
	}
	mshell->command_count++;
	mshell->last_pid = pid;
	if (exec->redir_fd[FD_IN] != STDIN_FILENO)
		close(exec->redir_fd[FD_IN]);
	if (exec->redir_fd[FD_OUT] != STDOUT_FILENO)
		close(exec->redir_fd[FD_OUT]);
	return (1);
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

	if (exec->redir_fd[FD_IN] != STDIN_FILENO)
	{
		original_stdin = dup(STDIN_FILENO);
		dup2(exec->redir_fd[FD_IN], STDIN_FILENO);
		close(exec->redir_fd[FD_IN]);
	}
	if (exec->redir_fd[FD_OUT] != STDOUT_FILENO)
	{
		original_stdout = dup(STDOUT_FILENO);
		dup2(exec->redir_fd[FD_OUT], STDOUT_FILENO);
		close(exec->redir_fd[FD_OUT]);
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

static void init_execution (t_execution *exec, t_ast *ast)
{
	exec->cmd_args = NULL;
	exec->redir_fd[FD_IN] = STDIN_FILENO;
	exec->redir_fd[FD_OUT] = STDOUT_FILENO;
	exec->has_next_pipe = (ast->next_right != NULL);
}

void execute_ast(t_minishell *mshell, t_ast *ast)
{
	t_ast *cmd_node;
	t_execution exec;
	int pipefd[2];
	pid_t pid;
	char **external_cmd;

	exec.prev_fd = STDIN_FILENO;
	ft_bzero(&exec, 0);

	while (ast)
	{
		init_execution(&exec, ast);
		cmd_node = NULL;

		if (exec.has_next_pipe && pipe(pipefd) < 0)
		{
			perror("pipe");
			return;
		}

		if (handle_redirections(ast, &exec) == FAIL)
		{
			mshell->exitcode = 1;
			ast = ast->next_right;
			continue;
		}

		cmd_node = get_cmd_node(ast);
		if (cmd_node)
			exec.cmd_args = cmd_node->cmd;

		//if only redirection is here like  < Makefile >out23
		if ((!exec.cmd_args || !exec.cmd_args[0]) &&
			(exec.redir_fd[FD_IN] != STDIN_FILENO || exec.redir_fd[FD_OUT] != STDOUT_FILENO))
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

		if (is_builtin(exec.cmd_args[0]) && !exec.has_next_pipe)
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
			setup_child_fds(exec.prev_fd, pipefd, exec.has_next_pipe, &exec);
			if (is_builtin(exec.cmd_args[0]))
			{
				execute_builtin(mshell, exec.cmd_args);
				delete_minishell(mshell);
				exit(mshell->exitcode);
			}
			if (!cmd_node)
			{
				ft_dprintf(2, "Giraffeshell: command node not found\n");
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
			if (exec.prev_fd != STDIN_FILENO)
				close(exec.prev_fd);
			if (exec.redir_fd[FD_IN] != STDIN_FILENO)
				close(exec.redir_fd[FD_IN]);
			if (exec.redir_fd[FD_OUT] != STDOUT_FILENO)
				close(exec.redir_fd[FD_OUT]);
			if (exec.has_next_pipe)
			{
				close(pipefd[1]);
				exec.prev_fd = pipefd[0];
			}
		}
		ast = ast->next_right;
	}
	mshell->exitcode = wait_for_children(mshell);
}
