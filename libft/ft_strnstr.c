/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:47:50 by aalahyan          #+#    #+#             */
/*   Updated: 2024/11/13 00:24:18 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;
	size_t	index;

	i = 0;
	if (!*(needle))
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			index = i;
			n = 0;
			while (needle[n] && haystack[i + n] == needle[n] && i + n < len)
				n++;
			if (needle[n] == 0)
				return ((char *)&haystack[index]);
		}
		i++;
	}
	return (NULL);
}
