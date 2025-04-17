
#include "../../inc/minishell.h"

// Initializes execution state before starting a pipeline
void init_execution_state(t_execution *exec, t_ast *ast)
{
	exec->cmd_args = NULL;
	exec->redir_fd[FD_IN] = STDIN_FILENO;
	exec->redir_fd[FD_OUT] = STDOUT_FILENO;
	exec->has_next_pipe = (ast->next_right != NULL);
}

int	is_builtin(const char *cmd)
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

void	execute_builtin_child(t_minishell *mshell, t_execution *exec)
{
		execute_builtin(mshell, exec->cmd_args);
		delete_minishell(mshell);
		exit(mshell->exitcode);

}


void handle_parent(t_minishell *mshell, t_execution *exec, int *pipefd, pid_t pid)
{
	mshell->command_count++;
	mshell->last_pid = pid;

	// Close write end of current pipe, we don't need it in parent
	if (exec->has_next_pipe)
		close(pipefd[1]);

	// Close the previous read end (we don't need it anymore)
	if (exec->prev_fd != STDIN_FILENO)
		close(exec->prev_fd);

	// Save the read end of this pipe to use as input for the next child
	exec->prev_fd = pipefd[0];
}


int execute_builtin_parent(t_minishell *mshell, t_execution *exec)
{
	int original_stdin = dup(STDIN_FILENO);
	int original_stdout = dup(STDOUT_FILENO);
	int status;

	if (original_stdin == -1 || original_stdout == -1)
	{
		perror("dup");
		return (1);
	}

	// Apply redirections
	if (exec->redir_fd[FD_IN] != STDIN_FILENO)
	{
		if (dup2(exec->redir_fd[FD_IN], STDIN_FILENO) == -1)
			perror("dup2 in");
		close(exec->redir_fd[FD_IN]);
	}
	if (exec->redir_fd[FD_OUT] != STDOUT_FILENO)
	{
		if (dup2(exec->redir_fd[FD_OUT], STDOUT_FILENO) == -1)
			perror("dup2 out");
		close(exec->redir_fd[FD_OUT]);
	}

	// Execute the builtin command in parent
	status = execute_builtin(mshell, exec->cmd_args); // You must implement run_builtin()

	// Restore original stdio
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);

	// Set shell's exit code
	mshell->exitcode = status;
	return (status);
}
