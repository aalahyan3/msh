/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 06:30:30 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/17 08:12:44 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"


static int get_size(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**get_rid_of_quotes(char **arr)
{
	char	**no_quotes;
	int		i;

	no_quotes = malloc(sizeof(char *) * (get_size(arr) + 1));
	if (!no_quotes)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		no_quotes[i] = expand_quotes(arr[i]);
		if (!no_quotes[i])
			return (free_2d_array(no_quotes), NULL);
		i++;
	}
	no_quotes[i] = NULL;
	return (no_quotes);
}

char	**expand_wildcards(char **arr)
{
	char	**no_quotes;

	no_quotes = get_rid_of_quotes(arr);
	free_2d_array(arr);
	return (no_quotes);
}

