/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:03:16 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/21 16:38:21 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_putstr(int fd, char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	write(fd, str, len);
}

static size_t	lenint(unsigned int n)
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

char	*ft_utoa_buf(unsigned int n, char *buf, size_t bufsize)
{
	size_t	len;

	len = lenint(n);
	if (bufsize <= len)
		return (NULL);
	buf[len] = '\0';
	while (len > 0)
	{
		len--;
		buf[len] = n % 10 + '0';
		n = n / 10;
	}
	return (buf);
}

unsigned int	get_signess(int sign, int n)
{
	unsigned int	unsigned_n;

	if (sign)
		unsigned_n = (unsigned int)(-(long)n);
	else
		unsigned_n = (unsigned int)n;
	return (unsigned_n);
}

char	*ft_itoa_buf(int n, char *buf, size_t bufsize)
{
	size_t			len;
	int				sign;
	unsigned int	unsigned_n;

	sign = (n < 0);
	unsigned_n = get_signess(sign, n);
	len = lenint(unsigned_n);
	if (len + 1 > bufsize)
		return (NULL);
	if (sign)
		len++;
	buf[len] = '\0';
	while (len > 0)
	{
		len--;
		buf[len] = unsigned_n % 10 + '0';
		unsigned_n /= 10;
	}
	if (sign)
		buf[0] = '-';
	return (buf);
}
