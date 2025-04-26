/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:37:35 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/26 20:59:55 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	safe_close(int fd)
{
	if (fd >= 0 && close(fd) == -1)
	{
		perror("close");
		return(FAIL);
	}
	return (SUCCESS);
}
