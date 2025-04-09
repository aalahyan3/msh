/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_expand_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:25:16 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/09 21:51:17 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*get_next_chunk(char *s, int *i)
{
	int		start;

	start = *i;
	if (!s[*i])
		return (NULL);
	if (s[*i] == '$')
		return (get_var_name(s, i));
	else
	{
		while (s[*i] && s[*i] != '$')
			*i += 1;
		return (ft_substr(s, start, *i - start));
	}
	return (NULL);
}

static char *expand_chunk(char *chunk, t_msh *msh, bool is_quote, bool end)
{


	if (*chunk)
	{
		if (is_quote || end)
			return(ft_strdup("$"));
		else
			return (ft_strdup(""));
	}
	else if (*chunk == '?')
	{
		
		return (ft_itoa(msh->last_exit));
	}
	else if (!ft_isalnum(*chunk) && *chunk != '_' && *chunk != '?')
	{
		return (ft_strdup(chunk));
	}
	return (ft_strdup(find_in_env(chunk, msh->env)));
}

static char	*expander(char *s, t_msh *msh, bool is_last)
{
	char	*chunk;
	char	*final;
	char	*temp;
	int		i;

	i = 0;
	final = NULL;
	chunk = get_next_chunk(s, &i);
	while (chunk)
	{
		if (*chunk == '$')
		{
			temp = chunk;
			chunk = expand_chunk(chunk + 1, msh, (*s == '"'), (!(s)[i] && is_last));
			free(temp);
		}
		if (!chunk)
			return (free(final), NULL);
		temp = ft_strjoin(final, chunk);
		free(final);
		free(chunk);
		if (!temp)
			return (NULL);
		final = temp;
		chunk = get_next_chunk(s, &i);
	}
	return (final);
}
static int	get_last(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i - 1);
}

char	**expand_string(char *str, t_msh *msh)
{
	char	**splited;
	int		i;
	int		last;
	char	*expanded;

	splited = split_by_quotes(str);
	if (!splited)
		return (NULL);
	last = get_last(splited);
	i = 0;
	while (splited[i])
	{
		if (*splited[i] != '\'' && ft_strchr(splited[i], '$'))
		{
			expanded = expander(splited[i], msh, i == last);
			free(splited[i]);
			splited[i] = expanded;
			if (!expanded)
				return (free_2d_array(splited), NULL);
		}
		i++;
	}
	return (join_and_split(splited));
}
