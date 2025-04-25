#include "../../inc/minishell.h"

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
