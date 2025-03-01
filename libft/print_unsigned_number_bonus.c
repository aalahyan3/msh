/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned_number_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:36:48 by aalahyan          #+#    #+#             */
/*   Updated: 2024/12/11 21:06:38 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_special_case(t_flags *flags, int *counter)
{
	int	i;

	i = 0;
	while (i < flags->field_w)
	{
		pf_putchar(' ', counter);
		i++;
	}
}

static void	print_right_alig(char *str, t_flags *flags, int *counter, int len)
{
	int	zeros;
	int	padding;

	padding = 0;
	zeros = 0;
	if (flags->precision > len && flags->precision >= 0)
		zeros = flags->precision - len;
	else if (flags->zero_pad == 1 && flags->field_w > len && \
			flags->precision == -1)
		zeros = flags->field_w - len;
	if (flags->field_w > len && flags->field_w > flags->precision)
		padding = flags->field_w - len - zeros;
	while (padding--)
		pf_putchar(' ', counter);
	while (zeros--)
		pf_putchar('0', counter);
	while (*str)
		pf_putchar(*str++, counter);
}

static void	print_left_alig(char *str, t_flags *flags, int *counter, int len)
{
	int	zeros;
	int	padding;

	padding = 0;
	zeros = 0;
	if (flags->precision > len && flags->precision >= 0)
		zeros = flags->precision - len;
	if (flags->field_w > len && flags->field_w > flags->precision)
		padding = flags->field_w - len - zeros;
	while (zeros--)
		pf_putchar('0', counter);
	while (*str)
		pf_putchar(*str++, counter);
	while (padding--)
		pf_putchar(' ', counter);
}

void	print_unsigned_number_bonus(unsigned int n, \
t_flags *flags, int *counter)
{
	char	decimal[11];
	char	buffer[11];
	int		i;

	i = 0;
	if (flags->precision == 0 && n == 0)
	{
		handle_special_case(flags, counter);
		return ;
	}
	ft_strlcpy(decimal, "0123456789", 11);
	if (n == 0)
		buffer[i++] = '0';
	while (n)
	{
		buffer[i++] = decimal[n % 10];
		n /= 10;
	}
	buffer[i] = 0;
	reverse_string(buffer, i);
	if (flags->left_alig == 1)
		print_left_alig(buffer, flags, counter, i);
	else
		print_right_alig(buffer, flags, counter, i);
}
