/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:44:28 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/17 08:48:22 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	**expand(char **arr, t_list *env_l)
{
	char	**vars_expanded;
	char	**wildcards_expanded;

	vars_expanded = expand_vars(arr, env_l);
	free_2d_array(arr);
	if (!vars_expanded)
		return (NULL);
	wildcards_expanded = expand_wildcards(vars_expanded);
	return (wildcards_expanded);
}
