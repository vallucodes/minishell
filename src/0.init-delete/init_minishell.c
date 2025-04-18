#include "minishell.h"

int	init_minishell(struct sigaction	*sa, t_minishell *mshell, char **envp, t_ast **ast)
{
	char	*path_str;

	if (copy_env(&mshell->envp, envp) != 0)
	{
		ft_dprintf(2, UNREACHABLE);
		return (FAIL);
	}
	mshell->exitcode = 0;
	mshell->last_pid = -1;
	mshell->sa = sa;
	mshell->path = NULL;
	mshell->arena = NULL;
	mshell->rl_count = 0;
	mshell->rl_count_heredoc = 0;
	*ast = NULL;
	path_str = get_env_value(mshell->envp->envp, "PATH");
	if (path_str)
		mshell->path = ft_split(path_str, ':');
	if (!mshell->path) //this can be also malloc fail
		ft_dprintf(2, "Giraffeshell: PATH not found in environment\n");
	init_signals(mshell->sa);

	//later add full struct
	// if (init_execution(&mshell->exec) != 0)
	//     return (1);
	return (0);
}

void	init_quotes(t_quotes_helper *quotes)
{
	quotes->in_double = 0;
	quotes->in_single = 0;
	quotes->in_quotes = 0;
	quotes->previous_in_quotes = 0;
}
