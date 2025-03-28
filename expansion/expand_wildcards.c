/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 06:30:30 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/28 20:51:50 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int	get_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i + 1);
}

char	**expand_wildcards(char **arr)
{
	char	***triple;
	int		i;

	triple = malloc(sizeof(char **) * get_size(arr));
	if (!triple)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		triple[i] = expand_string_2(arr[i]);
		if (!triple)
			return (free_triple_array(triple), NULL);
		i++;
	}
	triple[i] = NULL;
	return (triple_to_double(triple));
}
