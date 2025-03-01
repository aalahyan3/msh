/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_printf_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:16:33 by aalahyan          #+#    #+#             */
/*   Updated: 2024/12/11 21:07:04 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Warning !: the folowing function does not work 
with read-only strings. be careful
*/
void	reverse_string(char *str, int len)
{
	char	temp;
	int		i;

	i = 0;
	while (i < len / 2)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
		i++;
	}
}

int	is_flag(char c)
{
	if (c == '+' || c == '-' || c == ' ' || \
	c == '#' || ft_isdigit(c) || c == '.')
		return (1);
	else
		return (0);
}

void	print_invalid_flag(char *str, int *counter)
{
	while (*str && !is_format(*str))
		pf_putchar(*str++, counter);
	if (is_format(*str))
		pf_putchar(*str, counter);
}

void	print_persent(t_flags *flags, int *counter)
{
	int	padding;

	padding = 0;
	if (flags->field_w > 1)
		padding = flags->field_w - 1;
	if (flags->left_alig == 1)
	{
		pf_putchar('%', counter);
		while (padding--)
			pf_putchar(' ', counter);
	}
	else
	{
		while (padding--)
			pf_putchar(' ', counter);
		pf_putchar('%', counter);
	}
}

void	get_pad_and_zeros_int(t_flags *flags, int *pad, int *zer, int len)
{
	if (flags->precision > len)
		*zer = flags->precision - len;
	else if (flags->zero_pad == 1 && flags->precision == -1 \
	&& flags->field_w > len)
		*zer = flags->field_w - len;
	if (flags->field_w > len && flags->field_w > flags->precision)
		*pad = flags->field_w - len - (*zer);
}
