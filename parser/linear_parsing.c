/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:03:29 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/22 18:02:07 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	get_next_token_2(t_l_parse **tok, char *s, int *i)
{
	int	start;

	if (s[*i] == ')')
	{
		*i += 1;
		(*tok)->content = ft_strdup(")");
		(*tok)->type = L_CLOSE_P;
	}
	else if (s[*i] == ';')
	{
		*i += 1;
		(*tok)->content = ft_strdup(";");
		(*tok)->type = L_SEMICOLON;
	}
	else if (s[*i] == '|')
	{
		*i += 1;
		if (s[*i] == '|')
		{
			*i += 1;
			(*tok)->content = ft_strdup("||");
			(*tok)->type = L_OR;
		}
		else
		{
			(*tok)->content = ft_strdup("|");
			(*tok)->type = L_PIPE;
		}
	}
	else if (s[*i] == '&')
	{
		*i += 1;
		if (s[*i] == '&')
		{
			*i += 1;
			(*tok)->content = ft_strdup("&&");
			(*tok)->type = L_AND;
		}
		else
		{
			(*tok)->content = ft_strdup("&");
			(*tok)->type = L_AMPERCENT;
		}
	}
	else if (s[*i] == '>')
	{
		*i += 1;
		if (s[*i] == '>')
		{
			*i += 1;
			(*tok)->content = ft_strdup(">>");
		}
		else
			(*tok)->content = ft_strdup(">");
		(*tok)->type = L_REDIRECTION;
	}
	else if (s[*i] == '<')
	{
		*i += 1;
		if (s[*i] == '<')
		{
			*i += 1;
			(*tok)->content = ft_strdup("<<");
		}
		else
			(*tok)->content = ft_strdup("<");
		(*tok)->type = L_REDIRECTION;
	}
	else
	{
		(*tok)->type = L_WORD;
		start = *i;
		while (s[*i] && !ft_isspace(s[*i]) && s[*i] != '(' && s[*i] != ')' && s[*i] != '|' && s[*i] != '&' && s[*i] != ';' && s[*i] != '>' && s[*i] != '<')
			*i += 1;
		(*tok)->content = ft_substr(s, start, *i - start);
	}
	if (!(*tok)->content)
	{
		free(*tok);
		*tok = NULL;
	}
}

static t_l_parse	*get_next_token(char *s, int *i)
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

bool	compare_expectations(t_l_parse *prev, t_l_parse *curr)
{
	if (curr->type == L_AMPERCENT || curr->type == L_SEMICOLON)
	{
			ft_putstr_fd("msh: syntax error near unsupported token `", 2);
			ft_putstr_fd(curr->content, 2);
			ft_putstr_fd("'\n", 2);
			return (false);
	}
	if (!prev)
	{
		if (curr->type == L_CLOSE_P || curr->type == L_OR || curr->type == L_AND || curr->type == L_PIPE || curr->type == L_SEMICOLON || curr->type == L_AMPERCENT)
		{
			ft_putstr_fd("msh: syntax error near unexpected token `", 2);
			ft_putstr_fd(curr->content, 2);
			ft_putstr_fd("'\n", 2);
			return (false);
		}
	}
	else if (prev->type == L_OPEN_P)
	{
		if (curr->type == L_CLOSE_P || curr->type == L_OR || curr->type == L_AND || curr->type == L_PIPE || curr->type == L_SEMICOLON || curr->type == L_AMPERCENT || curr->type == L_REDIRECTION)
		{
			ft_putstr_fd("msh: syntax error near unexpected token `", 2);
			ft_putstr_fd(curr->content, 2);
			ft_putstr_fd("'\n", 2);
			return (false);
		}
	}
	else if (prev->type == L_OR || prev->type == L_AND || prev->type == L_PIPE || prev->type == L_SEMICOLON || prev->type == L_AMPERCENT || prev->type == L_REDIRECTION)
	{
		if (curr->type == L_CLOSE_P || curr->type == L_OR || curr->type == L_AND || curr->type == L_PIPE || curr->type == L_SEMICOLON || curr->type == L_AMPERCENT)
		{
			ft_putstr_fd("msh: syntax error near unexpected token `", 2);
			ft_putstr_fd(curr->content, 2);
			ft_putstr_fd("'\n", 2);
			return (false);
		}
	}
	else if (prev->type == L_CLOSE_P)
	{
		if (curr->type == L_WORD || curr->type == L_OPEN_P)
		{
			ft_putstr_fd("msh: syntax error near unexpected token `", 2);
			ft_putstr_fd(curr->content, 2);
			ft_putstr_fd("'\n", 2);
			return (false);
		}
	}
	else if (prev->type == L_WORD)
	{
		if (curr->type == L_OPEN_P)
		{
			ft_putstr_fd("msh: syntax error near unexpected token `", 2);
			ft_putstr_fd(curr->content, 2);
			ft_putstr_fd("'\n", 2);
			return (false);
		}
	}
	return (true);
}

bool	linear_parsing(char *s)
{
	t_l_parse	*token;
	t_l_parse	*prev;
	int			i;
	bool		no_error;

	i = 0;
	prev = NULL;
	token = get_next_token(s, &i);
	no_error = true;
	while (token)
	{
		if (!compare_expectations(prev, token))
		{
			no_error = false;
			break ;
		}
		if (prev)
		{
			free(prev->content);
			free(prev);
		}
		prev = token;
		token = get_next_token(s, &i);
	}
	if (prev)
	{
		if (prev->type == L_OPEN_P || prev->type == L_OR || prev->type == L_AND || prev->type == L_PIPE || prev->type == L_SEMICOLON || prev->type == L_AMPERCENT || prev->type == L_REDIRECTION)
		{
			ft_putstr_fd("msh: syntax error near unexpected token `newline'\n", 2);
			
			no_error = false;
		}
	free(prev->content);
	free(prev);
	}
	return (no_error);
}
