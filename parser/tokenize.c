/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:40:10 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/14 09:12:25 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tok	*get_next_token(char	*s, int *i)
{
	int		start;
	t_tok	*tok;

	while (s[*i] && ft_isspace(s[*i]))
		*i += 1;
	if (!s[*i])
		return (NULL);
	tok = malloc(sizeof(t_tok));
	if (!tok)
		return (NULL);
	start = *i;
	while (s[*i])
	{
		if (s[*i] == '|')
		{
			*i += 1;
			if (s[*i] && s[*i] == '|')
			{
				tok->content = ft_strdup("||");
				tok->type = OR;
				*i += 1;
			}
			else
			{
				tok->content = ft_strdup("|");
				tok->type = PIPE;
			}
			return (tok);
		}
		if (s[*i] == '&')
		{
			tok->content = ft_strdup("&&");
			tok->type = AND;
			*i += 2;
			return (tok);
		}
		else
		{
			while (s[*i] && s[*i] != '|' && s[*i] != '&')
			{
				if (s[*i] == '(')
				{
					skip_parentheses(s, i);
					continue;
				}
				if (s[*i] == '\'' || s[*i] == '\"')
				{
					skip_quotes(s, i, s[*i]);
					continue;
				}
				*i += 1;
			}
			tok->content = ft_substr(s, start, *i - start);
			tok->type = BLOCK;
			return (tok);
		}
	}
	free(tok);
	return (NULL);
}

t_list	*tokenize(char	*prompt)
{
	t_list	*tok_list;
	t_tok	*tok;
	int		i;

	i = 0;
	tok_list = NULL;
	tok = get_next_token(prompt, &i);
	while (tok)
	{
		ft_lstadd_back(&tok_list, ft_lstnew(tok));
		printf("tok: %s\n", tok->content);
		tok = get_next_token(prompt, &i);
	}
	return (tok_list);
}