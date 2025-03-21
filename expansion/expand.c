/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:44:28 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/21 13:51:48 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	**expand(char **arr, t_list *env_l)
{
	char	**vars_expanded;
	char	**wildcards_expanded;
	if (!arr)
		return (NULL);
	vars_expanded = expand_vars(arr, env_l);
	// free_2d_array(arr);
	if (!vars_expanded)
		return (NULL);
	return (vars_expanded);
	wildcards_expanded = expand_wildcards(vars_expanded);

	return (wildcards_expanded);
}
