/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:03:29 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/18 22:24:15 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static enum e_tok_type get_next_token(char *s, int *i)
{
	int		start;
	t_tok	token;

	while (s[*i] && ft_isspace(s[*i]))
		*i += 1;
	if (!s[*i])
		return (NONE);
	start = *i;
	while (s[*i])
	{
		if (s[*i] == '\'' || s[*i] == '"')
		{
			skip_quotes(s, i, s[*i]);
			return (WORD);
		}
		if (s[*i] == '<')
		{
			*i += 1;
			if (s[*i] == '<')
				*i += 1;
			return (SYMBOL);
		}
		if (s[*i] == '>')
		{
			*i += 1;
			if (s[*i] == '>')
				*i += 1;
			return (SYMBOL);
		}
		if (s[*i] == '|')
		{
			*i += 1;
			if (s[*i] == '|')
				*i += 1;
			return (SYMBOL);
		}
	}


}

bool	linear_parsing(char *s)
{
	int		i;
	enum e_tok_type	token;
	enum e_tok_type	prev;

	i = 0;
	prev = NONE;
	token = get_next_token(s, &i);
	while (token != NONE)
	{
		if (!compare_expections(token, prev))
			return (false);
		token = get_next_token(s, &i);
	}
	return (true);
}