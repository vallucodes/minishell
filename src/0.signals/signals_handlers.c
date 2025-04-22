#include "../../inc/minishell.h"

int	g_signal;

void	sigint_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = signal;
		close(STDIN_FILENO);
		write(STDOUT_FILENO, "\n", 1);
		set_exitcode_signal(NULL);
	}
}

void	sigint_handler_main(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = signal;
		set_exitcode_signal(NULL);
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

<<<<<<< HEAD
t_minishell *get_minishell(t_minishell *m)
{
	static t_minishell *minishell;

	if (m == NULL)
		return (minishell);
	minishell = m;
	return (NULL);
}

// void	sigint_handler_child(int signal)
// {
// 	if (signal == SIGINT)
// 		write(STDOUT_FILENO, "\n", 1);
// 	if (signal == SIGQUIT)
// 		ft_dprintf(2, "Quit, core dump\n");
// }
=======
void	sigint_handler_parent(int signal)
{
	if (signal == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	if (signal == SIGQUIT)
		ft_dprintf(2, "Quit, core dumped\n");
}

void	set_exitcode_signal(t_minishell *mshell)
{
	static t_minishell	*current_mshell;

	if (mshell)
		current_mshell = mshell;
	else if (g_signal != 0)
		current_mshell->exitcode = 128 + g_signal;
}
>>>>>>> main
