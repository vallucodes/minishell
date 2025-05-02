/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:59:23 by hiennguy          #+#    #+#             */
/*   Updated: 2025/05/02 13:54:51 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_current_directory(char *buffer, size_t size)
{
	if (!getcwd(buffer, size))
	{
		ft_dprintf(STDERR_FILENO,
			"cd: error retrieving current directory: "
			"getcwd: cannot access parent directories: %s\n",
			strerror(errno));
		return (FAIL);
	}
	return (SUCCESS);
}
