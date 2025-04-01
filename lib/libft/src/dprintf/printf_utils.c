/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:03:16 by vlopatin          #+#    #+#             */
/*   Updated: 2025/03/31 13:24:53 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_putstr(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
	}
}

static	int	lenint(unsigned int n)
{
	size_t	len;

	len = 0;
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	len++;
	return (len);
}

char	*ft_utoa(unsigned int n)
{
	char	*str;
	size_t	len;

	len = lenint(n);
	str = (char *)malloc(1 + len * sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		len--;
		str[len] = n % 10 + '0';
		n = n / 10;
	}
	return (str);
}
