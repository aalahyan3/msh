/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 06:30:30 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/21 17:32:09 by aalahyan         ###   ########.fr       */
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



char	**expand_wildcards(char **arr)
{
	char	***triple;

	triple = malloc(sizeof(char *8))
}

