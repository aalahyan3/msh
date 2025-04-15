/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:56:51 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/15 20:03:13 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int	get_size(char **splited)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (splited[i])
	{
		size += ft_strlen(splited[i]);
		i++;
	}
	return (size);
}

static void	remove_quotes(char **splited)
{
	int		i;
	char	*temp;

	i = 0;
	while (splited[i])
	{
		if (splited[i][0] == '\'' || splited[i][0] == '"')
		{
			temp = splited[i];
			splited[i] = ft_substr(temp, 1, ft_strlen(temp) - 2);
			free(temp);
		}
		i++;
	}
}

static char	*join_double(char **splited)
{
	int		i;
	char	*joined;
	int		size;

	size = get_size(splited);
	joined = malloc(sizeof(char) * (size + 1));
	if (!joined)
		return (NULL);
	i = 0;
	joined[0] = 0;
	while (splited[i])
	{
		if (*splited[i])
			ft_strlcat(joined, splited[i], size + 1);
		i++;
	}
	return (joined);
}

char	*expand_quotes_str(char *str)
{
	char	**splited;
	char	*joined;

	splited = split_by_quotes(str);
	if (!splited)
		return (NULL);
	remove_quotes(splited);
	joined = join_double(splited);
	free_2d_array(splited);
	return (joined);
}
