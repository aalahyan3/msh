/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:03:29 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/18 23:18:02 by aalahyan         ###   ########.fr       */
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
		else if (s[*i] == '<')
		{
			*i += 1;
			if (s[*i] == '<')
				*i += 1;
			else
				return (SYMBOL_1);
			return (SYMBOL_2);
		}
		else if (s[*i] == '>')
		{
			*i += 1;
			if (s[*i] == '>')
				*i += 1;
			else
				return (SYMBOL_1);
			return (SYMBOL_2);
		}
		else if (s[*i] == '|')
		{
			*i += 1;
			if (s[*i] == '|')
				*i += 1;
			else
				return (SYMBOL_1);
			return (SYMBOL_2);
		}
		else if (s[*i] == '&')
		{
			*i += 1;
			if (s[*i] == '&')
				*i += 1;
			else
				return (FORBIDDEN);
			return (SYMBOL_2);
		}
		else if (s[*i] == ';')
		{
			*i += 1;
			return (FORBIDDEN);
		}
		else if (s[*i] == '(' || s[*i] == ')')
		{
			*i += 1;
			return (SYMBOL_1);
		}
		else
		{
			while (s[*i] && !ft_isspace(s[*i]) && s[*i] != '\'' && s[*i] != '"' && s[*i] != '<' && s[*i] != '>' && s[*i] != '&' && s[*i] != '|' && s[*i] && s[*i] != ';' && s[*i] != '(' && s[*i] != ')')
				*i += 1;
			return (WORD);
		}
		*i += 1;
	}
	return (NONE);
}

bool	compare_expectations(enum e_tok_type tok, enum e_tok_type prev, char *s, int i)
{
	if (tok == FORBIDDEN)
		print_error(FORBIDDEN, s, i - 1, 1);
	if (tok == WORD)
		return (true);
	if ()

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
		// if (!compare_expections(token, prev))
		// 	return (false);
		printf("token: %d\n", token);
		token = get_next_token(s, &i);
	}
	return (true);
}