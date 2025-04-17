#include "../../inc/minishell.h"
#include <sys/wait.h>

int	wait_for_children(t_minishell *mshell)
{
	int	i;
	int	wstatus;
	int exit_code;

	i = 0;
	exit_code = 0;
	while (i < mshell->command_count)
	{
		if (mshell->last_pid == wait(&wstatus))
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
