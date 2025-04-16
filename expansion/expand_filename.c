/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:27:43 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/16 22:19:03 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int	get_size(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i + 1);
}

static char	**empty_filename(void)
{
	char	**arr;

	arr = malloc(2 * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[0] = ft_strdup("");
	if (!arr[0])
		return (free(arr), NULL);
	arr[1] = NULL;
	return (arr);
}

char	**expand_filename(char *name, t_msh *msh)
{
	char	**vars_expanded;
	char	***triple;
	int		i;

	if (!*name)
		return (empty_filename());
	vars_expanded = expand_string(name, msh);
	if (!vars_expanded)
		return (NULL);
	triple = malloc(sizeof(char **) * get_size(vars_expanded));
	if (!triple)
		return (free_2d_array(vars_expanded), NULL);
	i = 0;
	while (vars_expanded[i])
	{
		triple[i] = expand_string_2(vars_expanded[i], 0);
		if (!triple[i])
			return (free_2d_array(vars_expanded), \
			free_triple_array(triple), NULL);
		i++;
	}
	triple[i] = NULL;
	free_2d_array(vars_expanded);
	return (triple_to_double(triple));
}
