/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_gnl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:38:11 by aalahyan          #+#    #+#             */
/*   Updated: 2024/12/11 19:56:13 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_gnl(char *rest, const char *buffer)
{
	char	*joined_str;
	int		l1;
	int		l2;

	l1 = 0;
	l2 = 0;
	if (rest)
		l1 = (int)ft_strlen(rest);
	if (buffer)
		l2 = (int)ft_strlen(buffer);
	joined_str = malloc(sizeof(char) * (l1 + l2 + 1));
	if (!joined_str)
	{
		if (rest)
			free(rest);
		return (NULL);
	}
	if (rest)
		ft_memcpy(joined_str, rest, l1);
	if (buffer)
		ft_memcpy(joined_str + l1, buffer, l2);
	joined_str[l1 + l2] = 0;
	if (rest)
		free(rest);
	return (joined_str);
}
