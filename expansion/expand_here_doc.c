/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:52:06 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/08 22:40:30 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*get_next_chunk(char *s, int *i)
{
	int	start;

	start = *i;
	if (!s[*i])
		return (NULL);
	if (s[*i] != '$')
	{
		while (s[*i] && s[*i] != '$')
			*i += 1;
		return (ft_substr(s, start, *i - start));
	}
	else
	{
		*i += 1;
		while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_' || s[*i] == '?'))
			*i += 1;
		return (ft_substr(s, start, *i - start));
	}
	return (NULL);
}

static char	*expander(char *s, t_msh *msh)
{
	char	*var;

	if (*(s + 1) == '?')
		return (ft_itoa(msh->last_exit));
	var = ft_strdup(find_in_env(s + 1, msh->env));
	free(s);
	return (var);
}

char	*expand_here_doc(char *line, t_msh *msh)
{
	char	*final;
	char	*chunk;
	char	*temp;
	int		i;

	i = 0;
	final = NULL;
	while ((chunk = get_next_chunk(line, &i)))
	{
		if (*chunk == '$')
		{
			temp = expander(chunk, msh);
			free(chunk);
			chunk = temp;
		}
		temp = ft_strjoin(final, chunk);
		free(final);
		final = temp;
		free(chunk);
	}
	return (final);
}
