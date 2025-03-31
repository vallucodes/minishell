/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_types2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:07:35 by vlopatin          #+#    #+#             */
/*   Updated: 2025/03/31 13:31:23 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_string(int fd, va_list args)
{
	char	*value;

	value = va_arg(args, char *);
	if (!value)
	{
		ft_putstr(fd, "(null)");
		return (6);
	}
	else
		ft_putstr(fd, value);
	return (ft_strlen(value));
}

int	ft_putnbr_base(int fd, unsigned long nbr, char	*base)
{
	unsigned long	base_len;
	int				count;

	count = 0;
	base_len = ft_strlen(base);
	if (nbr >= base_len)
		count += ft_putnbr_base(fd, nbr / base_len, base);
	count += write(fd, &base[nbr % base_len], 1);
	return (count);
}
