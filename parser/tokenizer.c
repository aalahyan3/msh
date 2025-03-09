/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:27:19 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/09 22:38:40 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_quotes(char *s, int *i, char c)
{
	*i += 1;
	while (s[*i] && s[*i] != c)
		*i += 1;
	if (s[*i])
		*i += 1;
}

void skip_block(char *s, int *i)
{
	int	expected;

	expected = 1;
	while (s[*i] && expected)
	{
		if (s[*i] == '(')
			expected++;
		if (s[*i] == ')')
			expected--;
		if (s[*i] == '\'' || s[*i] == '"')
			skip_quotes(s, i, s[*i]);
		*i += 1;
	}
	if ( s[*i] && s[*i] == ')')
		*i += 1;
}

char	*get_full_block(char *s, int *i)
{
	int	start;

	start = *i;
	while (s[*i])
	{
		if (s[*i] == '\'' || s[*i] == '"')
			skip_quotes(s, i, s[*i]);
		if (s[*i] == '(')
			skip_block(s, i);
		if (s[*i] == '|' || s[*i] == '&')
			break ;
		*i += 1;
	}
	return (ft_substr(s, start, *i - start));
}

void	get_command(char *input, t_token **token, int *i)
{
	(*token)->value = get_full_block(input, i);
	(*token)->key = WORD;
	if (!(*token)->value)
	{
		free(*token);
		*token = NULL;
	}
}

void	get_next_token_2(char *input, t_token **token, int *i)
{
	if (input[*i] == '|')
	{
		if (input[*i + 1] == '|')
		{
			(*token)->value = NULL;
			(*token)->key = OR;
			*i += 1;
		}
		else
		{
			(*token)->value = NULL;
			(*token)->key = PIPE;
		}
		*i += 1;
	}
	else
		get_command(input, token ,i);
}

t_token	*get_next_token(char *input, int *i)
{
	t_token	*token;

	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		*i += 1;
	if (!input[*i])
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (input[*i] == '(')
	{
		token->value = get_block(input, i);
		if (!token->value)
			return (free(token), NULL);
		token->key = BLOCK;
	}
	else if (input[*i] == '&' && input[*i + 1] == '&')
	{
		token->value = NULL;
		token->key = AND;
		*i += 2;
	}
	else
		get_next_token_2(input, &token, i);
	return (token);
}

t_list	*tokenizer(char *input)
{
	t_token	*token;
	t_list	*tok_list;
	int		i;

	i = 0;
	tok_list = NULL;
	token = get_next_token(input, &i);
	while (token)
	{
		ft_lstadd_back(&tok_list, ft_lstnew(token));
		token = get_next_token(input, &i);
	}
	return (tok_list);
	// return (optimize_list(&tok_list));
}
