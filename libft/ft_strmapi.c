/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:50:01 by aalahyan          #+#    #+#             */
/*   Updated: 2024/10/28 22:12:04 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*mapped_string;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	mapped_string = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!mapped_string)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mapped_string[i] = f(i, s[i]);
		i++;
	}
	mapped_string[i] = 0;
	return (mapped_string);
}
