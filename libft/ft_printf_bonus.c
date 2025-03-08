/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:01:19 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/08 15:12:02 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		counter;
	t_flags	flags;

	counter = 0;
	va_start(args, format);
	while (*format)
	{
		while (*format && *format != '%')
			pf_putchar(*format++, &counter);
		if (*format && *format == '%')
		{
			format++;
			reset_flags(&flags);
			manage_flags(args, &flags, (char *)(format), &counter);
			while (*format && !is_format(*format))
				format++;
		}
		if (counter == -1)
			return (-1);
		if (*format)
			format++;
	}
	va_end(args);
	return (counter);
}
