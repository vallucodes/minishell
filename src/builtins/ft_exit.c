#include "../../inc/minishell.h"

void	ft_exit(char **ast_cmds, t_minishell *minishell)
{
	long	code;
	int		cmd_count;

	cmd_count = count_cmds(ast_cmds);
	write(STDERR_FILENO, "exit\n", 5);
	if (cmd_count == 1)
		exit(minishell->exitcode);
	if (!ft_atol(ast_cmds[1], &code))
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n", ast_cmds[1]);
		exit(2);
	}
	if (cmd_count > 2)
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		minishell->exitcode = 1;
		return ;
	}
	exit((unsigned char)code);
}

