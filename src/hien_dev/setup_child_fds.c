#include "../../inc/minishell.h"
#include <sys/wait.h>

static void redirect_input(int prev_fd, t_execution *exec)
{
	if (exec->redir_fd[FD_IN] != STDIN_FILENO)
		dup2(exec->redir_fd[FD_IN], STDIN_FILENO);
	else if (prev_fd != STDIN_FILENO)
		dup2(prev_fd, STDIN_FILENO);
}

static void redirect_output(int *pipefd, int has_next_pipe, t_execution *exec)
{
	if (exec->redir_fd[FD_OUT] != STDOUT_FILENO)
		dup2(exec->redir_fd[FD_OUT], STDOUT_FILENO);
	else if (has_next_pipe)
		dup2(pipefd[1], STDOUT_FILENO);
}

static void close_unneeded_fds(int prev_fd, int *pipefd, int has_next_pipe, t_execution *exec)
{
	if (exec->redir_fd[FD_IN] != STDIN_FILENO)
		close(exec->redir_fd[FD_IN]);
	if (exec->redir_fd[FD_OUT] != STDOUT_FILENO)
		close(exec->redir_fd[FD_OUT]);
	if (prev_fd != STDIN_FILENO)
		close(prev_fd);
	if (has_next_pipe)
	{
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void setup_child_fds(int prev_fd, int *pipefd, int has_next_pipe, t_execution *exec)
{
	redirect_input(prev_fd, exec);
	redirect_output(pipefd, has_next_pipe, exec);
	close_unneeded_fds(prev_fd, pipefd, has_next_pipe, exec);
}
