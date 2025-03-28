/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 21:03:19 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/28 19:57:33 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	valid_quote(char *s, int *i, char c)
{
	*i += 1;
	while (s[*i] && s[*i] != c)
		*i += 1;
	if (!s[*i])
	{
		ft_putstr_fd("msh: syntax error near unclosed quote ", 2);
		ft_putchar_fd('`', 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('`', 2);
		ft_putchar_fd('\n', 2);
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
			skip_quotes(s, i, s[*i]);
		if (s[*i] == '(')
			expect += 1;
		if (s[*i] == ')')
			expect -= 1;
		*i += 1;
	}
	if (expect)
	{
		ft_putstr_fd("msh: syntax error near unclosed parenthisis `)`\n", 2);
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
		{
			ft_putstr_fd("msh: syntax error near unexpected token `)'\n", 2);
			return (false);
		}
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
