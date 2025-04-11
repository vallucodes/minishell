#include "../../inc/minishell.h"

void	sigint_handler(int signal)
{
	printf("\nIntercepted SIGINT!\n");
}

void	init_signals(struct sigaction *sa)
{
	sa->sa_handler = sigint_handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
}

void	ignore_signal_action(struct sigaction *sa)
{
	sa->sa_handler = SIG_IGN;
	sigaction(SIGINT, sa, NULL);
}

void	restart_signal_action(struct sigaction *sa)
{
	sa->sa_handler = sigint_handler;
	sigaction(SIGINT, sa, NULL);
}
