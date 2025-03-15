/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_red_structs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:39:13 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/15 18:01:22 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_red_structs(t_reds **reds)
{
	int	i;

	i = 0;
	while (reds[i])
	{
		printf("freeing reds[%d]\n", i);
		free(reds[i]->file);
		free(reds[i]);
		i++;
	}
	free(reds);
	reds = NULL;
}