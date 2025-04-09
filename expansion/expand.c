/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:44:28 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/09 21:44:25 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	**expand(char **arr, t_msh *msh)
{
	char	**vars_expanded;
	char	**wildcards_expanded;

	for (int i = 0; arr[i]; i++)
		printf("arr []%s\n", arr[i]);
	if (!arr)
		return (NULL);
	vars_expanded = expand_vars(arr, msh);
	if (!vars_expanded)
		return (NULL);
	wildcards_expanded = expand_wildcards(vars_expanded);
	free_2d_array(vars_expanded);
	return (wildcards_expanded);
}
