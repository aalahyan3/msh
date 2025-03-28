/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:27:43 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/28 14:46:11 by aalahyan         ###   ########.fr       */
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

char	**expand_filename(char *name, t_msh *msh)
{
	char	**vars_expanded;
	char	***triple;
	int		i;

	if (!*name)
	{
		vars_expanded = malloc(sizeof(char *) * 2);
		if (!vars_expanded)
			return (NULL);
		vars_expanded[0] = ft_strdup("");
		if (!vars_expanded[0])
			return (free(vars_expanded), NULL);
		vars_expanded[1] = NULL;
		return (vars_expanded);
	}
	vars_expanded = expand_string(name, msh);
	if (!vars_expanded)
		return (NULL);
	triple = malloc(sizeof(char **) * get_size(vars_expanded));
	if (!triple)
		return (free_2d_array(vars_expanded), NULL);
	i = 0;
	while (vars_expanded[i])
	{
		triple[i] = expand_string_2(vars_expanded[i]);
		if (!triple[i])
			return (free_2d_array(vars_expanded), free_triple_array(triple), NULL);
		i++;
	}
	triple[i] = NULL;
	free_2d_array(vars_expanded);
	return (triple_to_double(triple));
}
