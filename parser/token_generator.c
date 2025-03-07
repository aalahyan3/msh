/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 18:12:30 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/07 00:25:46 by aalahyan         ###   ########.fr       */
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

int	get_word(t_token *token, char *input, int *i)
{
	int	start;

	start = *i;
	while (input[*i] && !token_symbol(input[*i]))
		*i += 1;
	token->value = ft_substr(input, start, *i - start);
	if (!token->value)
		return (0);
	if (token->value[0] == '\'')
		token->key = WORD_SQ;
	else if (token->value[0] == '\"')
		token->key = WORD_DQ;
	else if (ft_strchr(token->value, '*'))
		token->key = WILD_CARD;
	else
		token->key = WORD;
	return (1);
}
