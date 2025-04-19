#include "../../inc/minishell.h"

int setup_pipe(t_exec *exec)
{
	if (exec->has_pipe)
	{
		if (pipe(exec->pipefd) < 0)
		{
			ft_dprintf(2, "Giraffeshell: %s: %s\n", "pipe", strerror(errno));
			return FAIL;
		}
	}
	return SUCCESS;
}

int setup_fork(t_exec *exec)
{
	exec->pid = fork();
	if (exec->pid < 0)
	{
		ft_dprintf(2, "Giraffeshell: %s: %s\n", "fork", strerror(errno));
		if (exec->has_pipe)
		{
			close(exec->pipefd[0]);
			close(exec->pipefd[1]);
		}
		return (FAIL);
	}
	else
	{
		exec->last_pid = exec->pid;
	}
	return (SUCCESS);
}

void setup_child_pipe_fds(t_minishell *mshell, t_exec *exec)
{
	if (exec->prev_fd != -1)
	{
		if (safe_dup2(exec->prev_fd, STDIN_FILENO) == FAIL)
		{
			ft_dprintf(2, "Giraffeshell: %s: %s\n", "dup2", strerror(errno));
			delete_minishell(mshell);
			exit(FAIL);
		}
		close(exec->prev_fd);
	}
	if (exec->has_pipe)
	{
		close(exec->pipefd[0]);
		if (safe_dup2(exec->pipefd[1], STDOUT_FILENO) == FAIL)
		{
			ft_dprintf(2, "Giraffeshell: %s: %s\n", "dup2", strerror(errno));
			delete_minishell(mshell);
			exit(FAIL);
		}
		close(exec->pipefd[1]);
	}
}

void setup_parent_pipe_fds(t_exec *exec)
{
	exec->command_count++;
	if (exec->prev_fd != -1)
		close(exec->prev_fd);

	if (exec->has_pipe)
	{
		close(exec->pipefd[1]);
		exec->prev_fd = exec->pipefd[0];
	}
}
