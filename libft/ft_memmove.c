/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 11:38:09 by aalahyan          #+#    #+#             */
/*   Updated: 2024/11/11 17:07:34 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*source;
	unsigned char	*dest;

	if ((!dst && !src) || (!dst && len == 0))
		return (NULL);
	if (dst == src)
		return (dst);
	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (dest < source)
	{
		while (len--)
			*dest++ = *source++;
	}
	else
	{
		while (len--)
			dest[len] = source[len];
	}
	return (dst);
}
