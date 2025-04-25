/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:01:11 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/25 21:01:15 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_env **my_env, char **argv)
{
	unsigned int	i;
	int				arg_count;

	if (!my_env || !(*my_env) || !(*my_env)->envp)
		return (FAIL);
	arg_count = count_argv(&argv[1]);
	if (arg_count > 0)
	{
		ft_dprintf(STDERR_FILENO, "Giraffeshell: env: too many arguments\n");
		return (FAIL);
	}
	i = 0;
	while (i < (*my_env)->len)
	{
		if ((*my_env)->envp[i] && ft_strchr((*my_env)->envp[i], '='))
			printf("%s\n", (*my_env)->envp[i]);
		i++;
	}
	return (SUCCESS);
}
