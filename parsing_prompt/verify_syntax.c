/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:43:40 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/01 13:50:01 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static bool	verify_double_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			while (str[i] && str[i] != '\"')
				i++;
			if (!str[i])
				return (false);
		}
		i++;
	}
	return (true);
}

void	verify_syntax(char *str)
{
	if (!verify_double_quotes(str))
		ft_printf("not double quoted!");
}
