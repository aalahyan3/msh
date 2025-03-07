/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:51:47 by aalahyan          #+#    #+#             */
/*   Updated: 2024/11/11 21:00:31 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_string;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	i = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && is_set(set, s1[start]))
		start++;
	while (s1[end] && is_set(set, s1[end]) && end >= start)
		end--;
	trimmed_string = malloc((end - start + 2) * sizeof(char));
	if (!trimmed_string)
		return (NULL);
	while (start <= end)
		trimmed_string[i++] = s1[start++];
	trimmed_string[i] = 0;
	return (trimmed_string);
}
