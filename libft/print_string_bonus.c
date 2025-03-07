/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:06:38 by aalahyan          #+#    #+#             */
/*   Updated: 2024/12/11 21:06:17 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	pf_putstr(char *str, int *counter, int len)
{
	while (len--)
	{
		pf_putchar(*str++, counter);
		if (*counter == -1)
			return ;
	}
}

static void	print_left_alig(char *str, t_flags *flags, int *counter, int len)
{
	int		padding;

	padding = 0;
	if (flags->precision < len && flags->precision >= 0)
		len = flags->precision;
	if (flags->field_w > len)
		padding = flags->field_w - len;
	pf_putstr(str, counter, len);
	if (*counter == -1)
		return ;
	while (padding--)
	{
		pf_putchar(' ', counter);
	}
}

static void	print_right_alig(char *str, t_flags *flags, int *counter, int len)
{
	int		padding;
	char	pad;

	padding = 0;
	if (flags->zero_pad == 1)
		pad = '0';
	else
		pad = ' ';
	if (flags->precision < len && flags->precision >= 0)
		len = flags->precision;
	if (flags->field_w > len)
		padding = flags->field_w - len;
	while (padding--)
	{
		pf_putchar(pad, counter);
	}
	pf_putstr(str, counter, len);
	if (*counter == -1)
		return ;
}

void	print_string_bonus(char *str, t_flags *flags, int *counter)
{
	int	len;

	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (flags->left_alig == 1)
		print_left_alig(str, flags, counter, len);
	else
		print_right_alig(str, flags, counter, len);
}
