/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:01:34 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/25 21:48:02 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_num_arg(char **argv, t_minishell *mshell)
{
	ft_dprintf(2, "Giraffeshell: exit: %s: numeric argument required\n",
		argv[1]);
	delete_minishell(mshell);
	exit(2);
}

void	ft_exit(char **argv, t_minishell *mshell)
{
	long	code;
	int		argv_count;

	argv_count = count_argv(argv);
	if (mshell->in_child == 0)
		ft_dprintf(1, "exit\n");
	if (argv_count == 1)
	{
		delete_minishell(mshell);
		exit(mshell->exitcode);
	}
	if (!ft_atol(argv[1], &code))
		check_num_arg(argv, mshell);
	if (argv_count > 2)
	{
		ft_dprintf(2, "Giraffeshell: exit: too many arguments\n");
		mshell->exitcode = 1;
		return ;
	}
	delete_minishell(mshell);
	exit((unsigned char)code);
}
