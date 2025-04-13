/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:54:23 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/13 18:28:10 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	skipper(char *s, int *i, int q, int p)
{
	if ((s[*i] == '\'' || s[*i] == '"') && q)
	{
		skip_quotes(s, i, s[*i]);
		return (1);
	}
	if (s[*i] == '(' && p)
	{
		skip_parentheses(s, i);
		return (1);
	}
	return (0);
}

char	*get_next_red(char *s, int *i)
{
	int	start;

	while (s[*i])
	{
		if (skipper(s, i, 1, 1))
			continue ;
		if (s[*i] && (s[*i] == '>' || s[*i] == '<'))
		{
			start = *i;
			while (s[*i] && (s[*i] == '>' || s[*i] == '<'))
				*i += 1;
			while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
				*i += 1;
			while (s[*i] && !ft_strchr(" \t<>", s[*i]))
			{
				if (skipper(s, i, 1, 0))
					continue ;
				*i += 1;
			}
			return (ft_substr(s, start, *i - start));
		}
		*i += 1;
	}
	return (NULL);
}
