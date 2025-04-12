#include "../../inc/minishell.h"

void	ft_exit(char **argv, t_minishell *minishell)
{
	long	code;
	int		argv_count;

	argv_count = count_argv(argv);
	write(STDERR_FILENO, "exit\n", 5);
	if (argv_count == 1)
		exit(minishell->exitcode);
	if (!ft_atol(argv[1], &code))
	{
		ft_dprintf(2, "Giraffeshell: exit: %s: numeric argument required\n", argv[1]);
		exit(2);
	}
	if (argv_count > 2)
	{
		ft_dprintf(2, "Giraffeshell: exit: too many arguments\n");
		minishell->exitcode = 1;
		return ;
	}
	exit((unsigned char)code);
}

