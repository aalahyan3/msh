/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:18:39 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/06 16:50:57 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	skipper(char *s, int *i)
{
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\t' \
			|| s[*i] == '<' || s[*i] == '>'))
	{
		if (s[*i] == '<' || s[*i] == '>')
		{
			(*i)++;
			while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
				(*i)++;
			while (s[*i] && s[*i] != ' ' && s[*i] != '\t' \
			&& s[*i] != '<' && s[*i] != '>')
			{
				if (s[*i] == '\'' || s[*i] =='"')
				{
					skip_quotes(s, i, s[*i]);
					continue ;
				}
				(*i)++;
			}
		}
		else
			(*i)++;
	}
}

char	*get_next_cmd(char *s, int *i)
{
	int	start;

	while (s[*i])
	{
		skipper(s, i);
		if (s[*i] && s[*i] != '<' && s[*i] != '>')
		{
			start = *i;
			while (s[*i] && s[*i] != ' ' && s[*i] != '\t' \
			&& s[*i] != '<' && s[*i] != '>')
			{
				if (s[*i] == '\'' || s[*i] == '"')
					skip_quotes(s, i, s[*i]);
				else
					(*i)++;
			}
			return (ft_substr(s, start, *i - start));
		}
	}
	return (NULL);
}
