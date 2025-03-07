/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_signed_number_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:45:35 by aalahyan          #+#    #+#             */
/*   Updated: 2024/12/11 21:05:55 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_special_case(t_flags *flags, int *counter)
{
	int	padding;

	padding = flags->space;
	if (flags->field_w > 0)
		padding = flags->field_w;
	if (flags->plus == 1 && flags->field_w > 0)
		padding = flags->field_w - 1;
	if (flags->left_alig == 1)
	{
		if (flags->plus == 1)
			pf_putchar('+', counter);
		while (padding--)
			pf_putchar(' ', counter);
	}
	else
	{
		while (padding--)
			pf_putchar(' ', counter);
		if (flags->plus == 1)
			pf_putchar('+', counter);
	}
}

static void	print_right_alig(char *str, t_flags *flags, int *counter, int n)
{
	int	zeros;
	int	len;
	int	padding;

	len = ft_strlen(str);
	zeros = 0;
	padding = 0;
	get_pad_and_zeros_int(flags, &padding, &zeros, len);
	while (padding--)
	{
		pf_putchar(' ', counter);
	}
	if (flags->plus == 1 && n >= 0)
		pf_putchar('+', counter);
	else if (flags->space == 1 && n >= 0)
		pf_putchar(' ', counter);
	if (n < 0)
		pf_putchar('-', counter);
	while (zeros--)
		pf_putchar('0', counter);
	while (*str)
		pf_putchar(*str++, counter);
}

static void	print_left_alig(char *str, t_flags *flags, int *counter, int n)
{
	int	zeros;
	int	len;
	int	padding;

	len = ft_strlen(str);
	padding = 0;
	zeros = 0;
	if (flags->precision > len)
		zeros = flags->precision - len;
	if (flags->field_w > len && flags->field_w > flags->precision)
		padding = flags->field_w - len - zeros;
	if (flags->plus == 1 && n >= 0)
		pf_putchar('+', counter);
	else if (flags->space == 1 && n >= 0)
		pf_putchar(' ', counter);
	if (n < 0)
		pf_putchar('-', counter);
	while (zeros--)
		pf_putchar('0', counter);
	while (*str)
		pf_putchar(*str++, counter);
	while (padding--)
		pf_putchar(' ', counter);
}

static void	print_signed_number_2(char *str, t_flags *flags, \
int *counter, int n)
{
	if ((flags->plus == 1 || flags->space == 1) || n < 0)
		flags->field_w = flags->field_w - 1;
	if (flags->right_alig == 1)
		print_right_alig(str, flags, counter, n);
	else
		print_left_alig(str, flags, counter, n);
}

void	print_signed_number_bonus(int n, t_flags *flags, int *counter)
{
	char	buffer[12];
	int		i;
	long	nb;

	if (n == 0 && flags->precision == 0)
	{
		handle_special_case(flags, counter);
		return ;
	}
	i = 0;
	nb = (long)n;
	if (nb == 0)
		buffer[i++] = '0';
	if (nb < 0)
		nb = -nb;
	while (nb)
	{
		buffer[i++] = (nb % 10) + '0';
		nb /= 10;
	}
	buffer[i] = 0;
	reverse_string(buffer, i);
	print_signed_number_2(buffer, flags, counter, n);
}
