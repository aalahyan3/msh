/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:12:30 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/08 16:37:38 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	token_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == ' ' || c == '\t')
		return (true);
	return (false);
}

char	*get_block(char *input, int *i)
{
	int	start;
	int	expected;

	start = *i;
	expected = 1;
	*i += 1;
	if (!input[*i])
		return (NULL);
	while (input[*i])
	{
		if (input[*i] == '(')
			expected++;
		else if (input[*i] == ')')
			expected--;
		*i += 1;
		if (expected == 0)
			break ;
	}
	return (ft_substr(input, start, *i - start));
}

void	get_exp(t_token **token, char *input, int *i)
{
	int	start;

	start = *i;

	while (input[*i] && !token_symbol(input[*i]))
		*i += 1;
	*i += 1;
	(*token)->value = ft_substr(input, start, *i - start);
	(*token)->key = WORD;
	if (!(*token)->value)
	{
		free(*token);
		*token = NULL;
	}
}

void	get_quoted(t_token **token, char *input, int *i, char quote)
{
	int	start;

	start = *i;
	*i += 1;
	while (input[*i] && input[*i] != quote)
		*i += 1;
	*i += 1;
	(*token)->value = ft_substr(input, start, *i - start);
	if (quote == '\'')
		(*token)->key = WORD_SQ;
	else
		(*token)->key = WORD_DQ;
	if (!(*token)->value)
	{
		free(*token);
		*token = NULL;
	}
}

int	get_word(t_token **token, char *input, int *i)
{
	if (input[*i] == '\'' || input[*i] == '"')
		get_quoted(token, input, i, input[*i]);
	else
		get_exp(token, input, i);
	return (1);
}
