/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:31:46 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/26 22:01:12 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	safe_dup2(int fd, int target_fd)
{
	if (dup2(fd, target_fd) < 0)
	{
		perror("dup2");
		if (close(fd) == -1)
			perror("close");
		return (FAIL);
	}
	return (SUCCESS);
}
