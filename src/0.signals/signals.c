#include "../../inc/minishell.h"

// int	init_signals(struct sigaction *sa)
// {
// 	g_signal = 0;
// 	sa->sa_handler = sigint_handler_main;
// 	if (sigemptyset(&sa->sa_mask) == -1)
// 	{
// 		perror("sigemptyset");
// 		return (FAIL);
// 	}
// 	sa->sa_flags = 0;
// 	if (sigaction(SIGINT, sa, NULL) == -1)
// 	{
// 		perror("sigaction");
// 		return (FAIL);
// 	}
// 	return (SUCCESS);
// }

int	signal_action_ignore(void)
{
	if (signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		perror("sigaction");
		return (FAIL);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("sigaction");
		return (FAIL);
	}
	return (SUCCESS);
}

int	signal_action_main(void)
{
	if (signal(SIGINT, sigint_handler_main) == SIG_ERR)
	{
		perror("sigaction");
		return (FAIL);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		return (FAIL);
	}
	return (SUCCESS);
}

int	signal_action_heredoc(void)
{
	if (signal(SIGINT, sigint_handler_heredoc) == SIG_ERR)
	{
		perror("signal");
		return (FAIL);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		return (FAIL);
	}
	return (SUCCESS);
}

int	signal_action_parent(void)
{
	if (signal(SIGINT, sigint_handler_parent) == SIG_ERR)
	{
		perror("signal");
		return (FAIL);
	}
	if (signal(SIGQUIT, sigint_handler_parent) == SIG_ERR)
	{
		perror("signal");
		return (FAIL);
	}
	return (SUCCESS);
}

int	signal_action_default(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		perror("signal");
		return (FAIL);
	}
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		perror("signal");
		return (FAIL);
	}
	return (SUCCESS);
}
