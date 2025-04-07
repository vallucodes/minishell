/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:48:02 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/03 18:17:22 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_2d(char **all_words)
{
	int	i;

	if (!all_words)
		return ;
	i = 0;
	while (all_words[i])
	{
		free(all_words[i]);
		i++;
	}
	free(all_words);
}
