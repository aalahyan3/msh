/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:13:32 by aalahyan          #+#    #+#             */
/*   Updated: 2024/11/11 21:13:04 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		size;
	long	nb;

	nb = n;
	size = count_digits(n);
	arr = malloc(sizeof(char) * (size + 1));
	if (!arr)
		return (NULL);
	arr[size--] = 0;
	if (nb == 0)
		arr[0] = '0';
	if (nb < 0)
	{
		arr[0] = '-';
		nb = -nb;
	}
	while (nb)
	{
		arr[size--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (arr);
}
