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

// int	signal_action_ignore(struct sigaction *sa)
// {
// 	sa->sa_handler = SIG_IGN;
// 	if (sigaction(SIGINT, sa, NULL) == -1)
// 	{
// 		perror("sigaction");
// 		return (FAIL);
// 	}
// 	return (SUCCESS);
// }

// int	signal_action_main(struct sigaction *sa)
// {
// 	g_signal = 0;
// 	sa->sa_handler = sigint_handler_main;
// 	if (sigaction(SIGINT, sa, NULL) == -1)
// 	{
// 		perror("sigaction");
// 		return (FAIL);
// 	}
// 	sa->sa_handler = SIG_IGN;
// 	if (sigaction(SIGQUIT, sa, NULL) == -1)
// 	{
// 		perror("sigaction");
// 		return (FAIL);
// 	}
// 	return (SUCCESS);
// }

// int	signal_action_heredoc(struct sigaction *sa)
// {
// 	sa->sa_handler = sigint_handler_heredoc;
// 	if (sigaction(SIGINT, sa, NULL) == -1)
// 	{
// 		perror("sigaction");
// 		return (FAIL);
// 	}
// 	sa->sa_handler = SIG_IGN;
// 	if (sigaction(SIGQUIT, sa, NULL) == -1)
// 	{
// 		perror("sigaction");
// 		return (FAIL);
// 	}
// 	return (SUCCESS);
// }

// void	signal_action_child(struct sigaction *sa)
// {
// 	sa->sa_handler = ;
// 	sigaction(SIGINT, sa, NULL);
// 	sa->sa_handler = ;
// 	sigaction(SIGQUIT, sa, NULL);
// }



void	init_signals(struct sigaction *sa)
{
	g_signal = 0;
	sa->sa_handler = sigint_handler_main;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
}

void	signal_action_ignore(struct sigaction *sa)
{
	sa->sa_handler = SIG_IGN;
	sigaction(SIGINT, sa, NULL);
}

void	signal_action_main(struct sigaction *sa)
{
	g_signal = 0;
	sa->sa_handler = sigint_handler_main;
	sigaction(SIGINT, sa, NULL);
	sa->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa, NULL);
}

void	signal_action_heredoc(struct sigaction *sa)
{
	sa->sa_handler = sigint_handler_heredoc;
	sigaction(SIGINT, sa, NULL);
	sa->sa_handler = SIG_IGN;
	sigaction(SIGQUIT, sa, NULL);
}
