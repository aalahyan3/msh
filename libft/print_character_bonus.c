/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_character_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:00:15 by aalahyan          #+#    #+#             */
/*   Updated: 2024/12/11 21:04:06 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_left_alig(char c, t_flags *flags, int *counter)
{
	int	padding;

	padding = 0;
	if (flags->field_w > 1)
		padding = flags->field_w - 1;
	pf_putchar(c, counter);
	while (padding--)
		pf_putchar(' ', counter);
}

static void	print_right_alig(char c, t_flags *flags, int *counter)
{
	int		padding;
	char	pad;

	padding = 0;
	if (flags->zero_pad == 1)
		pad = '0';
	else
		pad = ' ';
	if (flags->field_w > 0)
		padding = flags->field_w - 1;
	while (padding--)
		pf_putchar(pad, counter);
	pf_putchar(c, counter);
}

void	print_character_bonus(char c, t_flags *flags, int *counter)
{
	if (flags->left_alig == 1)
		print_left_alig(c, flags, counter);
	else
		print_right_alig(c, flags, counter);
}
