/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_adress_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 15:12:13 by aalahyan          #+#    #+#             */
/*   Updated: 2024/12/11 21:04:53 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_left_alig(char *str, t_flags *flags, int *counter, int len)
{
	int	padding;
	int	zeros;

	padding = 0;
	zeros = 0;
	flags->field_w = flags->field_w - 2;
	if (flags->precision > len)
		zeros = flags->precision - len;
	if (flags->field_w > len)
		padding = flags->field_w - len - zeros;
	pf_putchar('0', counter);
	pf_putchar('x', counter);
	while (zeros--)
		pf_putchar('0', counter);
	while (*str)
		pf_putchar(*str++, counter);
	while (padding--)
		pf_putchar(' ', counter);
}

static void	print_right_alig(char *str, t_flags *flags, int *counter, int len)
{
	int	padding;
	int	zeros;

	padding = 0;
	zeros = 0;
	flags->field_w = flags->field_w - 2;
	if (flags->precision > len)
		zeros = flags->precision - len;
	else if (flags->zero_pad == 1 && flags->field_w > len)
		zeros = flags->field_w - len;
	if (flags->field_w > len)
		padding = flags->field_w - len - zeros;
	while (padding--)
		pf_putchar(' ', counter);
	pf_putchar('0', counter);
	pf_putchar('x', counter);
	while (zeros--)
		pf_putchar('0', counter);
	while (*str)
		pf_putchar(*str++, counter);
}

void	print_adress_bonus(void *ptr, t_flags *flags, int *counter)
{
	unsigned long	addr;
	int				i;
	char			hex[17];
	char			buff[17];

	addr = (unsigned long)ptr;
	ft_strlcpy(hex, "0123456789abcdef", 17);
	i = 0;
	if (addr == 0)
		buff[i++] = '0';
	while (addr)
	{
		buff[i++] = hex[addr % 16];
		addr /= 16;
	}
	buff[i] = 0;
	reverse_string(buff, i);
	if (flags->left_alig == 1)
		print_left_alig(buff, flags, counter, i);
	else
		print_right_alig(buff, flags, counter, i);
}
