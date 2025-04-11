/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:03:19 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/10 15:49:54 by aalahyan         ###   ########.fr       */
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

bool	valid_parentheses(char *s, int *i)
{
	int	expect;

	expect = 1;
	*i += 1;
	while (s[*i] && expect)
	{
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			skip_quotes(s, i, s[*i]);
			continue ;
		}
		if (s[*i] == '(')
			expect += 1;
		if (s[*i] == ')')
			expect -= 1;
		*i += 1;
	}
	if (expect)
	{
		ft_printf_error("syntax error near unclosed parenthisis `)`\n", \
		NULL, NULL, NULL);
		return (false);
	}
	return (true);
}

static bool	is_parenthisis(char *s)
{
	int		i;
	int		before;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			skip_quotes(s, &i, s[i]);
			i--;
			continue ;
		}
		if (s[i] == '(')
		{
			before = i;
			if (!valid_parentheses(s, &i))
				return (false);
			continue ;
		}
		if (s[i] == ')')
			return (ft_printf_error("syntax error near unexpected token `)\n", \
			NULL, NULL, NULL), false);
	}
	return (true);
}

bool	initial_checks(char *s)
{
	if (!valid_quotes(s))
		return (false);
	if (!is_parenthisis(s))
		return (false);
	if (!valid_blocks(s))
		return (false);
	return (true);
}
