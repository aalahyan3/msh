/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_red_structs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:39:13 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/16 19:42:49 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_red_structs(t_reds **reds)
{
	int	i;

	i = 0;
	while (reds[i])
	{
		free(reds[i]->file);
		reds[i]->file = NULL;
		free(reds[i]);
		reds[i] = NULL;
		i++;
	}
	free(reds);
	reds = NULL;
}