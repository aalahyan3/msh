/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:44:28 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/16 22:06:19 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	restore_var_quotes(char **arr)
{
	int		i;
	int		j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] == SQUOTE_PACEHOLDER)
				arr[i][j] = '\'';
			else if (arr[i][j] == DQUOTE_PACEHOLDER)
				arr[i][j] = '\"';
			j++;
		}
		i++;
	}
}

char	**expand(char **arr, t_msh *msh, int export)
{
	char	**vars_expanded;
	char	**wildcards_expanded;

	if (!arr)
		return (NULL);
	vars_expanded = expand_vars(arr, msh);
	if (!vars_expanded)
		return (NULL);
	wildcards_expanded = expand_wildcards(vars_expanded, export);
	free_2d_array(vars_expanded);
	if (!wildcards_expanded)
		return (NULL);
	restore_var_quotes(wildcards_expanded);
	return (wildcards_expanded);
}
