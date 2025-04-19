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

	mshell->sa = sa;
	mshell->path = NULL;
	mshell->arena = NULL;
	mshell->origin_stdin = dup(STDIN_FILENO);
	mshell->origin_stdout = dup(STDOUT_FILENO);
	if (mshell->origin_stdin < 0 || mshell->origin_stdout < 0)
		return (FAIL);
	*ast = NULL;
	path_str = get_env_value(mshell->envp->envp, "PATH");
	if (path_str)
		mshell->path = ft_split(path_str, ':');
	if (!mshell->path) //this can be also malloc fail
		ft_dprintf(2, "Giraffeshell: PATH not found in environment\n");
	init_signals(mshell->sa);
	return (0);
}

void	init_quotes(t_quotes_helper *quotes)
{
	quotes->in_double = 0;
	quotes->in_single = 0;
	quotes->in_quotes = 0;
	quotes->previous_in_quotes = 0;
}
