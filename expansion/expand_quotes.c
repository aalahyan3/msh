/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 07:02:17 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/17 09:58:55 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	remove_quotes(char **s)
{
	int		i;
	char	*temp;
	int		len;

	i = 0;
	while (s[i])
	{
		len = ft_strlen(s[i]);
		if (len >= 2 && (*s[i] == '"' \
		|| *s[i] == '\'') && s[i][len - 1] == *s[i])
		{
			temp = ft_substr(s[i], 1, len - 2);
			free(s[i]);
			s[i] = temp;
		}
		i++;
	}
}

char	*expand_quotes(char *s)
{
	char	**splited;
	char	*temp;
	char	*final;
	int		i;

	splited = split_by_quotes(s);
	if (!splited)
		return (NULL);
	remove_quotes(splited);
	final = NULL;
	i = 0;
	while (splited[i])
	{
		temp = ft_strjoin(final, splited[i]);
		free(final);
		final = temp;
		i++;
	}
	free_2d_array(splited);
	return (final);
}
