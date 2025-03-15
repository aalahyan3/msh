/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:39:02 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/15 18:01:39 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "free_utils.h"

void	free_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("freeing arr[%d]\n", i);
		free(arr[i]);
		i++;
	}
	free(arr);
}
