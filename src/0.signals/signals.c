#include "../../inc/minishell.h"

bool	sig_action_ignore(t_minishell *mshell)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	return (SUCCESS);
}

bool	sig_action_main(t_minishell *mshell)
{
	g_signal = 0;
	if (signal(SIGINT, sigint_handler_main) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	return (SUCCESS);
}

bool	sig_action_heredoc(t_minishell *mshell)
{
	g_signal = 0;
	if (signal(SIGINT, sigint_handler_heredoc) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	return (SUCCESS);
}

bool	sig_action_parent(t_minishell *mshell)
{
	if (signal(SIGINT, sigint_handler_parent) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	if (signal(SIGQUIT, sigint_handler_parent) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	return (SUCCESS);
}

bool	sig_action_default(t_minishell *mshell)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	return (SUCCESS);
}
