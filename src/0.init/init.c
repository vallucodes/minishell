
#include "minishell.h"

int	init_minishell(t_minishell *mshell, char **envp)
{
	if (copy_env(&mshell->envp, envp) != 0)
	{
		ft_dprintf(2, "Environment copy fail");
		return (FAIL);
	}
	mshell->exitcode = 0;
	// if (init_ast(&mshell->ast) != 0)
	//     return (1);

	//later add full struct
	// if (init_execution(&mshell->exec) != 0)
	//     return (1);

	// if (init_signal_handling() != 0)
	//     return (1);

	// mshell->exit_code = 0;

	return (0);
}

void	init_quotes(t_quotes_helper *quotes)
{
	quotes->in_double = 0;
	quotes->in_single = 0;
	quotes->in_quotes = 0;
	quotes->previous_in_quotes = 0;
}
