/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_red.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:54:23 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/12 14:46:24 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_next_red(char *s, int *i)
{
	int	start;

	while (s[*i])
	{
		if (s[*i] == '(')
		{
			skip_parentheses(s, i);
			continue ;
		}
		if (s[*i] && (s[*i] == '>' || s[*i] == '<'))
		{
			start = *i;
			while (s[*i] && (s[*i] == '>' || s[*i] == '<'))
				*i += 1;
			while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
				*i += 1;
			while (s[*i] && !ft_strchr(" \t<>", s[*i]))
			{

				if (s[*i] == '\'' || s[*i] == '"')
				{
					skip_quotes(s, i, s[*i]);
					continue ;
				}
				*i += 1;
			}
			return (ft_substr(s, start, *i - start));
		}
		*i += 1;
	}
	return (NULL);
}
