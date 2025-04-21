#include "../../inc/minishell.h"

int	sig_action_ignore(t_minishell *mshell)
{
	printf("sig_action_ignore is set\n");
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	return (SUCCESS);
}

int	sig_action_main(t_minishell *mshell)
{
	printf("sig_action_main is set\n");
	g_signal = 0;
	if (signal(SIGINT, sigint_handler_main) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	return (SUCCESS);
}

int	sig_action_heredoc(t_minishell *mshell)
{
	printf("sig_action_heredoc is set\n");
	g_signal = 0;
	if (signal(SIGINT, sigint_handler_heredoc) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	return (SUCCESS);
}

int	sig_action_parent(t_minishell *mshell)
{
	printf("sig_action_parent is set\n");
	if (signal(SIGINT, sigint_handler_parent) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	if (signal(SIGQUIT, sigint_handler_parent) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	return (SUCCESS);
}

int	sig_action_default(t_minishell *mshell)
{
	printf("sig_action_def is set\n");
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		exit_cleanup_error(mshell, "sigaction");
	return (SUCCESS);
}
