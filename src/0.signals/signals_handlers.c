#include "../../inc/minishell.h"

int	g_signal;

void	sigint_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = signal;
		close(STDIN_FILENO);
		write(STDOUT_FILENO, "\n", 1);
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

// void	sigint_handler_child(int signal)
// {
// 	if (signal == SIGINT)
// 		write(STDOUT_FILENO, "\n", 1);
// 	if (signal == SIGQUIT)
// 		ft_dprintf(2, "Quit, core dump\n");
// }
