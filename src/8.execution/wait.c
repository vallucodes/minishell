#include "../../inc/minishell.h"
#include <sys/wait.h>

int	wait_for_children(t_exec *exec)
{
	int	i;
	int	wstatus;
	int exit_code;

	i = 0;
	exit_code = 0;
	while (i < exec->command_count)
	{
		if (exec->last_pid == wait(&wstatus))
		{
			if (WIFEXITED(wstatus))
				exit_code = WEXITSTATUS(wstatus);
			else if (WIFSIGNALED(wstatus))
				exit_code = 128 + WTERMSIG(wstatus);
		}
		i++;
	}
	return (exit_code);
}


// int wait_for_children2(t_exec *exec)
// {
// 	int status;
// 	pid_t pid;
// 	int exit_code = 0;

// 	while ((pid = wait(&status)) > 0)
// 	{
// 		if (pid == exec->last_pid)
// 		{
// 			if (WIFEXITED(status))
// 				exit_code = WEXITSTATUS(status);
// 			else if (WIFSIGNALED(status))
// 				exit_code = 128 + WTERMSIG(status);
// 		}
// 	}
// 	return (exit_code);
// }
