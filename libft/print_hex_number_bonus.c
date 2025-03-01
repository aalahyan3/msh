/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_number_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 17:28:47 by aalahyan          #+#    #+#             */
/*   Updated: 2024/12/11 21:05:05 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_special_case(t_flags *flags, unsigned int n, int *counter)
{
	int	i;

	i = 0;
	if (flags->precision == 0 && n == 0)
	{
		while (i < flags->field_w)
		{
			pf_putchar(' ', counter);
			i++;
		}
		return (1);
	}
	return (0);
}

static void	print_ox(int *counter, char type)
{
	pf_putchar('0', counter);
	if (type == 'x')
		pf_putchar('x', counter);
	else
		pf_putchar('X', counter);
}

static void	print_left_alig(char *str, t_flags *flags, \
int *counter, char type)
{
	int	padding;
	int	zeros;
	int	len;

	padding = 0;
	zeros = 0;
	len = ft_strlen(str);
	if (flags->hash == 1 && str[0] != '0')
		flags->field_w = flags->field_w - 2;
	if (flags->precision > len && flags->precision >= 0)
		zeros = flags->precision - len;
	if (flags->field_w > len && flags->field_w > flags->precision)
		padding = flags->field_w - len - zeros;
	if (flags->hash == 1 && str[0] != '0')
		print_ox(counter, type);
	while (zeros--)
		pf_putchar('0', counter);
	while (*str)
		pf_putchar(*str++, counter);
	while (padding--)
		pf_putchar(' ', counter);
}

static void	print_right_alig(char *str, t_flags *flags, \
int *counter, char type)
{
	int	padding;
	int	zeros;
	int	len;

	padding = 0;
	zeros = 0;
	len = ft_strlen(str);
	if (flags->hash == 1 && str[0] != '0')
		flags->field_w = flags->field_w - 2;
	if (flags->precision > len && flags->precision >= 0)
		zeros = flags->precision - len;
	else if (flags->zero_pad == 1 && flags->field_w > len && \
			flags->precision == -1)
		zeros = flags->field_w - len;
	if (flags->field_w > len && flags->field_w > flags->precision)
		padding = flags->field_w - len - zeros;
	while (padding--)
		pf_putchar(' ', counter);
	if (flags->hash == 1 && str[0] != '0')
		print_ox(counter, type);
	while (zeros--)
		pf_putchar('0', counter);
	while (*str)
		pf_putchar(*str++, counter);
}

void	print_hex_number_bonus(unsigned int n, t_flags *flags, \
int *counter, char type)
{
	char	hex[17];
	char	buffer[17];
	int		i;

	i = 0;
	if (handle_special_case(flags, n, counter))
		return ;
	if (type == 'x')
		ft_strlcpy(hex, "0123456789abcdef", 17);
	else
		ft_strlcpy(hex, "0123456789ABCDEF", 17);
	if (n == 0)
		buffer[i++] = '0';
	while (n)
	{
		buffer[i++] = hex[n % 16];
		n /= 16;
	}
	buffer[i] = 0;
	reverse_string(buffer, i);
	if (flags->left_alig == 1)
		print_left_alig(buffer, flags, counter, type);
	else
		print_right_alig(buffer, flags, counter, type);
}
