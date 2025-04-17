/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:03:01 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/16 16:45:44 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_atol_overflow(long result, int digit, int sign)
{
	if (sign == 1 && result > (LONG_MAX - digit) / 10)
		return (1);
	if (sign == -1 && (-result) < (LONG_MIN + digit) / 10)
		return (1);
	return (0);
}

static int	handle_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

int	ft_atol(const char *str, long *out)
{
	long	result;
	int		sign;
	int		digit;

	result = 0;
	if (!str || !str[0])
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = handle_sign(&str);
	if (*str < '0' || *str > '9')
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (check_atol_overflow(result, digit, sign))
			return (0);
		result = result * 10 + digit;
		str++;
	}
	if (*str != '\0')
		return (0);
	*out = result * sign;
	return (1);
}
