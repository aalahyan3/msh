/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:31:16 by aalahyan          #+#    #+#             */
/*   Updated: 2025/01/24 19:57:32 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_overflow(long long n, int sign, int mod)
{
	if (n > (LONG_MAX / 10) || (n == LONG_MAX / 10 && mod > LONG_MAX % 10))
	{
		if (sign == -1)
			return (0);
		else
			return (-1);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long long	result;
	int			sign;
	int			overflow;

	result = 0;
	sign = 1;
	while (*str && (*str == 32 || (*str >= 9 && *str <= 13)))
		str++;
	if (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		overflow = handle_overflow(result, sign, *str - '0');
		if (overflow == 0 || overflow == -1)
			return (overflow);
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
