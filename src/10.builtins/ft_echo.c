/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:00:50 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/25 21:00:52 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_valid_n_flag(const char *arg);

int	ft_echo(int argv_count, char **argv)
{
	int	word_index;
	int	newline;

	word_index = 1;
	newline = 1;
	while (word_index < argv_count && is_valid_n_flag(argv[word_index]))
	{
		newline = 0;
		word_index++;
	}
	while (word_index < argv_count)
	{
		ft_dprintf(STDOUT_FILENO, "%s", argv[word_index]);
		if (word_index + 1 < argv_count)
			ft_dprintf(STDOUT_FILENO, " ");
		word_index++;
	}
	if (newline)
		ft_dprintf(STDOUT_FILENO, "\n");
	return (SUCCESS);
}

static int	is_valid_n_flag(const char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}
