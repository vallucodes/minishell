/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:03:01 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/02 15:13:37 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		check_overflow(long result, int digit, int sign)
{
	if (sign == 1 && result > (LONG_MAX - digit) / 10)
		return (1);
	if (sign == -1 && -result < (LONG_MIN + digit) / 10)
		return (1);
	return (0);
}

long	handle_overflow(int sign)
{
	if (sign == 1)
		return (LONG_MAX);
	return (LONG_MIN);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;
	int		digit;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (check_overflow(result, digit, sign))
			return (handle_overflow(sign));
		result = result * 10 + digit;
		str++;
	}
	return (result * sign);
}
