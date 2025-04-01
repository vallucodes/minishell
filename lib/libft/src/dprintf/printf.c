/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:34:19 by vlopatin          #+#    #+#             */
/*   Updated: 2025/03/31 13:25:19 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static int	is_identifier(int fd, va_list args, char a)
{
	int	c;

	c = 0;
	if (a == 'c')
		c += ft_char(fd, args);
	else if (a == 's')
		c += ft_string(fd, args);
	else if (a == 'p')
		c += ft_pointer(fd, args);
	else if (a == 'd' || a == 'i')
		c += ft_int(fd, args);
	else if (a == 'u')
		c += ft_unsigned_int(fd, args);
	else if (a == 'x')
		c += ft_hex(fd, args, "lower");
	else if (a == 'X')
		c += ft_hex(fd, args, "upper");
	else if (a == '%')
		c += write(fd, "%", 1);
	return (c);
}

int	ft_dprintf(int fd, const char *s, ...)
{
	va_list		args;
	int			i;
	int			c;

	va_start (args, s);
	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == '%' && (!ft_strchr("cspdiuxX%", s[i + 1]) || \
				s[i + 1] == '\0'))
			return (-1);
		if (s[i] == '%' && ft_strchr("cspdiuxX%", s[i + 1]))
		{
			c += is_identifier(fd, args, s[i + 1]);
			i++;
		}
		else
			c += write(fd, &s[i], 1);
		i++;
	}
	va_end (args);
	return (c);
}
