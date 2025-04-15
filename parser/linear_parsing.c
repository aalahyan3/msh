/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 22:03:29 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/15 14:28:32 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static bool	print_unexpected_token(char *token)
{
	ft_printf_error("syntax error near unexpected token `", token, "'\n", NULL);
	return (false);
}

static void	print_unexpected_newline(t_l_parse *token, bool *no_error)
{
	if (!token)
		return ;
	if (*no_error && (token->type == L_OPEN_P || token->type == L_OR \
	|| token->type == L_AND || token->type == L_PIPE \
	|| token->type == L_SEMICOLON || token->type == L_AMPERCENT \
	|| token->type == L_REDIRECTION))
	{
		ft_printf_error("syntax error near unexpected token `newline'\n", \
		NULL, NULL, NULL);
		*no_error = false;
	}
	free(token->content);
	free(token);
}

static bool	is_unexpected_token(t_l_parse *prev, t_l_parse *curr)
{
	if (!prev)
		return (curr->type == L_CLOSE_P || curr->type == L_OR \
		|| curr->type == L_AND || curr->type == L_PIPE \
		|| curr->type == L_SEMICOLON || curr->type == L_AMPERCENT);
	if (prev->type == L_OPEN_P)
		return (curr->type == L_CLOSE_P || curr->type == L_OR \
		|| curr->type == L_AND || curr->type == L_PIPE \
		|| curr->type == L_SEMICOLON || curr->type == L_AMPERCENT);
	if (prev->type == L_OR || prev->type == L_AND || prev->type == L_PIPE \
	|| prev->type == L_SEMICOLON || prev->type == L_AMPERCENT \
	|| prev->type == L_REDIRECTION)
		return (curr->type == L_CLOSE_P || curr->type == L_OR \
		|| curr->type == L_AND || curr->type == L_PIPE \
		|| curr->type == L_SEMICOLON || curr->type == L_AMPERCENT \
		|| curr->type == prev->type);
	if (prev->type == L_CLOSE_P)
		return (curr->type == L_WORD || curr->type == L_OPEN_P);
	if (prev->type == L_WORD)
		return (curr->type == L_OPEN_P);
	return (false);
}

bool	compare_expectations(t_l_parse *prev, t_l_parse *curr)
{
	if (curr->type == L_AMPERCENT || curr->type == L_SEMICOLON)
	{
		ft_printf_error("syntax error near unsupported token `", \
		curr->content, "'\n", NULL);
		return (false);
	}
	if (is_unexpected_token(prev, curr))
		return (print_unexpected_token(curr->content));
	return (true);
}

bool	linear_parsing(char *s)
{
	t_l_parse	*token;
	t_l_parse	*prev;
	int			i;
	bool		no_error;

	1 && (i = 0, prev = NULL, token = get_next_token(s, &i), no_error = true);
	while (token)
	{
		if (!compare_expectations(prev, token))
		{
			free(token->content);
			free(token);
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
	print_unexpected_newline(prev, &no_error);
	return (no_error);
}
