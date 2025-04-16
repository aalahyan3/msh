/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:03:19 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/16 10:50:13 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	valid_quote(char *s, int *i, char c)
{
	char	b[2];

	b[0] = c;
	b[1] = '\0';
	*i += 1;
	while (s[*i] && s[*i] != c)
		*i += 1;
	if (!s[*i])
	{
		ft_printf_error("syntax error near unclosed quote `", b, "`\n", NULL);
		return (false);
	}
	*i += 1;
	return (true);
}

static bool	valid_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			if (!valid_quote(s, &i, s[i]))
				return (false);
			continue ;
		}
		i++;
	}
	return (true);
}

bool	initial_checks(char *s)
{
	if (!valid_quotes(s))
		return (false);
	if (!valid_blocks(s))
		return (false);
	return (true);
}
