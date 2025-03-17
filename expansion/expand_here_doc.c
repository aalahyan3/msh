/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:52:06 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/17 13:25:41 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "expansion.h"

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
		while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
			*i += 1;
		return (ft_substr(s, start, *i - start));
	}
	return (NULL);
}

static char	*expander(char *s, t_list *env_l)
{
	char	*var;

	var = ft_strdup(find_in_env(s + 1, env_l));
	free(s);
	return (var);
}

char	*expand_here_doc(char *line, t_list *env_l)
{
	char	*final;
	char	*chunk;
	char	*temp;
	int		i;

	i = 0;
	chunk = get_next_chunk(line, &i);
	final = NULL;
	while (chunk)
	{
		printf("%s\n", chunk);
		
		if (*chunk == '$')
			chunk = expander(chunk, env_l);
		temp = ft_strjoin(final, chunk);
		free(final);
		final = temp;
		chunk = get_next_chunk(line, &i);
	}
	return (final);
}