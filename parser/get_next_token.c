/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:54:47 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/15 20:13:24 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	get_next_token_5(t_l_parse **tok, char *s, int *i)
{
	int	start;

	(*tok)->type = L_WORD;
	start = *i;
	while (s[*i] && !ft_isspace(s[*i]) && s[*i] != '(' \
	&& s[*i] != ')' && s[*i] != '|' && s[*i] != '&' \
	&& s[*i] != ';' && s[*i] != '>' && s[*i] != '<')
	{
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			skip_quotes(s, i, s[*i]);
			continue ;
		}
		*i += 1;
	}
	(*tok)->content = ft_substr(s, start, *i - start);
	if (!(*tok)->content)
	{
		free(*tok);
		*tok = NULL;
	}
}

void	get_next_token_4(t_l_parse **tok, char *s, int *i)
{
	int	start;

	if (s[*i] == '>' || s[*i] == '<')
	{
		start = *i;
		if (s[*i] == '<')
		{
				while (s[*i] && s[*i] == s[start] && *i - start <= 2)
					*i += 1;
		}
		else
		{
			while (s[*i] && s[*i] == s[start] && *i - start < 2)
				*i += 1;
		}
		(*tok)->content = ft_substr(s, start, *i - start);
		(*tok)->type = L_REDIRECTION;
		return ;
	}
	get_next_token_5(tok, s, i);
}

void	get_next_token_3(t_l_parse **tok, char *s, int *i)
{
	if (s[*i] == '|')
	{
		*i += 1;
		if (s[*i] == '|')
		{
			*i += 1;
			1 && ((*tok)->content = ft_strdup("||"), (*tok)->type = L_OR);
		}
		else
			1 && ((*tok)->content = ft_strdup("|"), (*tok)->type = L_PIPE);
		return ;
	}
	else if (s[*i] == '&')
	{
		*i += 1;
		if (s[*i] == '&')
		{
			*i += 1;
			1 && ((*tok)->content = ft_strdup("&&"), (*tok)->type = L_AND);
		}
		else
			1 && ((*tok)->content = ft_strdup("&"), (*tok)->type = L_AMPERCENT);
		return ;
	}
	get_next_token_4(tok, s, i);
}

void	get_next_token_2(t_l_parse **tok, char *s, int *i)
{
	if (s[*i] == ')')
	{
		*i += 1;
		(*tok)->content = ft_strdup(")");
		(*tok)->type = L_CLOSE_P;
		return ;
	}
	else if (s[*i] == ';')
	{
		*i += 1;
		(*tok)->content = ft_strdup(";");
		(*tok)->type = L_SEMICOLON;
		return ;
	}
	get_next_token_3(tok, s, i);
}

t_l_parse	*get_next_token(char *s, int *i)
{
	t_l_parse	*tok;

	while (s[*i] && ft_isspace(s[*i]))
		*i += 1;
	if (!s[*i])
		return (NULL);
	tok = malloc(sizeof(t_l_parse));
	if (!tok)
		return (NULL);
	if (s[*i] == '(')
	{
		*i += 1;
		tok->content = ft_strdup("(");
		tok->type = L_OPEN_P;
		if (!tok->content)
		{
			free(tok);
			return (NULL);
		}
		return (tok);
	}
	get_next_token_2(&tok, s, i);
	return (tok);
}
