/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_msh_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:07:05 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/09 18:07:59 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh_malloc.h"

void	*msh_malloc(size_t size)
{
	void	*ptr;
	static int i = 1;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	printf("[%d] allocated in : %p\n", i++, ptr);
	return (ptr);
}