/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:27:19 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/09 09:38:26 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_next_token_4(char *input, t_token **token, int *i)
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
		get_word(token, input, i);
}

int	get_next_token_3(char *input, t_token **token, int *i)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			(*token)->value = ft_strdup(">>");
			(*token)->key = APPEND;
			if (!(*token)->value)
				return (free(*token), *token = NULL, 1);
			*i += 1;
		}
		else
		{
			(*token)->value = ft_strdup(">");
			(*token)->key = REDIRECT_OUT;
			if (!(*token)->value)
				return (free(*token), *token = NULL);
		}
		*i += 1;
	}
	else
		get_next_token_4(input, token, i);

}

int	get_next_token_2(char *input, t_token **token, int *i)
{
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			(*token)->value = ft_strdup("<<");
			(*token)->key = HERE_DOC;
			if (!(*token)->value)
				return (free(*token), *token = NULL);
			*i += 1;
		}
		else
		{
			(*token)->value = ft_strdup("<");
			(*token)->key = REDIRECT_IN;
			if (!(*token)->value)
				return (free(*token), *token = NULL);
		}
		*i += 1;
	}
	else
		get_next_token_3(input, token, i);
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
