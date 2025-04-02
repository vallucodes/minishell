#include "../../inc/minishell.h"

void	ft_exit(char **args, t_minishell *minishell)
{
	long	code;
	int		arg_count;

	arg_count = 0;
	while (args[arg_count])
		arg_count++;

	write(STDERR_FILENO, "exit\n", 5);

	if (arg_count == 1)
		exit(minishell->exitcode);
	if (!ft_atol(args[1], &code))
	{
		fprintf(stderr, "minishell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}
	if (arg_count > 2)
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		minishell->exitcode = 1;
		return ;
	}
	exit((unsigned char)code);
}

