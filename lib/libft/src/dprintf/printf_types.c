/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:07:57 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/16 16:11:13 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

int	ft_char(int fd, va_list args)
{
	char	value;

	value = va_arg(args, int);
	write(fd, &value, 1);
	return (1);
}

int	ft_hex(int fd, va_list args, char *case_type)
{
	unsigned int	value;
	int				count;

	count = 0;
	value = va_arg(args, unsigned int);
	if (ft_strncmp(case_type, "lower", ft_strlen("upper")) == 0)
		count += ft_putnbr_base(fd, (unsigned long)value, "0123456789abcdef");
	else if (ft_strncmp(case_type, "upper", ft_strlen("upper")) == 0)
		count += ft_putnbr_base(fd, (unsigned long)value, "0123456789ABCDEF");
	return (count);
}

int	ft_int(int fd, va_list args)
{
	int		value;
	int		str_len;
	char	buf[12];
	char	*itoa_str;

	value = va_arg(args, int);
	itoa_str = ft_itoa_buf(value, buf, sizeof(buf));
	ft_putstr(fd, itoa_str);
	str_len = ft_strlen(itoa_str);
	return (str_len);
}

int	ft_unsigned_int(int fd, va_list args)
{
	unsigned int	value;
	int				str_len;
	char			buf[12];
	char			*utoa_str;

	value = va_arg (args, unsigned int);
	utoa_str = ft_utoa_buf(value, buf, sizeof(buf));
	ft_putstr(fd, utoa_str);
	str_len = ft_strlen(utoa_str);
	return (str_len);
}

int	ft_pointer(int fd, va_list args)
{
	void	*value;
	int		count;

	count = 0;
	value = va_arg(args, void *);
	if (value == 0)
		count += write(fd, "(nil)", 5);
	else
	{
		count += write(fd, "0x", 2);
		count += ft_putnbr_base(fd, (unsigned long)value, "0123456789abcdef");
	}
	return (count);
}
