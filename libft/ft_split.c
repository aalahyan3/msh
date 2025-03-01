/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:56:26 by aalahyan          #+#    #+#             */
/*   Updated: 2025/01/04 17:20:23 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(char const *s, char c)
{
	int	size;

	size = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			size++;
			s++;
		}
		while (*s && *s != c)
			s++;
	}
	return (size + 1);
}

static char	*get_word(char const *start, char c)
{
	char	*word;
	char	*word_start;
	char	*ptr;
	int		size;

	size = 0;
	ptr = (char *)start;
	while (*ptr && *ptr != c)
	{
		size++;
		ptr++;
	}
	word = malloc (sizeof(char) * (size + 1));
	if (!word)
		return (NULL);
	word_start = word;
	while (start < ptr)
		*word++ = *start++;
	*word = 0;
	return (word_start);
}

static void	*free_array(char **array, int allocated)
{
	int	i;

	i = 0;
	while (i < allocated)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;

	if (!s || !*s)
		return (NULL);
	array = malloc(sizeof (char *) * (get_size(s, c)));
	if (!array)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			array[i] = get_word(s, c);
			if (array[i] == NULL)
				return (free_array(array, i));
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	array[i] = NULL;
	return (array);
}
