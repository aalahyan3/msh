/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_join_and_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:12:47 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/09 22:17:40 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static char	*join_array(char **arr)
{
	char	*final;
	char	*temp;
	int		i;

	i = 0;
	final = NULL;
	while (arr[i])
	{
		temp = ft_strjoin(final, arr[i]);
		free(final);
		if (!temp)
			return (NULL);
		final = temp;
		i++;
	}
	return (final);
}

char	**join_and_split(char **arr)
{
	char	*joined;

	joined = join_array(arr);
	free_2d_array(arr);
	if (!joined)
		return (NULL);
	return (split_not_quotes(joined));
}
