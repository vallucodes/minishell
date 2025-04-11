#include "../../inc/minishell.h"

int	g_signal;

void sigint_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = signal;
		close(STDIN_FILENO);
	}
}

void	sigint_handler_main(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// g_signal = signal;
}

void	init_signals(struct sigaction *sa)
{
	g_signal = 0;
	sa->sa_handler = sigint_handler_main;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
}

void	ignore_signal_action(struct sigaction *sa)
{
	sa->sa_handler = SIG_IGN;
	sigaction(SIGINT, sa, NULL);
}

void	restart_signal_action_main(struct sigaction *sa)
{
	g_signal = 0;
	sa->sa_handler = sigint_handler_main;
	sigaction(SIGINT, sa, NULL);
}

void	restart_signal_action_heredoc(struct sigaction *sa)
{
	sa->sa_handler = sigint_handler_heredoc;
	sigaction(SIGINT, sa, NULL);
}
