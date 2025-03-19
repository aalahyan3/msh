/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_by_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 22:02:03 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/18 16:59:29 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*get_next_chunk(char *s, int *i)
{
	int	start;

	if (!s || !*s)
		return (NULL);
	start = *i;
	if (s[*i] == '\'' || s[*i] == '"')
	{
		skip_quotes(s, i, s[*i]);
		if (start == *i)
			return (NULL);
		return (ft_substr(s, start, *i - start));
	}
	else
	{
		while (s[*i] && s[*i] != '\'' && s[*i] != '"')
			*i += 1;
		if (start == *i)
			return (NULL);
		return (ft_substr(s, start, *i - start));
	}
}

static int	get_size(char *s)
{
	int		i;
	int		size;
	char	*ch;

	size = 0;
	i = 0;
	ch = get_next_chunk(s, &i);
	while (ch)
	{
		free(ch);
		size++;
		ch = get_next_chunk(s, &i);
	}
	return (size + 1);
}

char	**split_by_quotes(char *s)
{
	int		i;
	char	**arr;
	char	*chunk;
	int		j;

	i = 0;
	arr = malloc(sizeof(char *) * get_size(s));
	if (!arr)
		return (NULL);
	chunk = get_next_chunk(s, &i);
	j = 0;
	while (chunk)
	{
		arr[j++] = chunk;
		chunk = get_next_chunk(s, &i);
	}
	arr[j] = NULL;
	return (arr);
}
