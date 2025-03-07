/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 14:38:07 by aalahyan          #+#    #+#             */
/*   Updated: 2025/01/24 17:54:57 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*gnl_free_and_null(void *p1, void *p2)
{
	if (p1)
	{
		free(p1);
		p1 = NULL;
	}
	if (p2)
	{
		free(p2);
		p2 = NULL;
	}
	return (NULL);
}

static char	*gnl_extract_rest(char *rest, int fd)
{
	char	*buffer;
	int		ret_val;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	ret_val = 1;
	while (!ft_char_exist(rest, '\n') && ret_val != 0)
	{
		ret_val = (int)read(fd, buffer, BUFFER_SIZE);
		if (ret_val < 0)
			return (gnl_free_and_null(buffer, rest));
		buffer[ret_val] = 0;
		rest = ft_strjoin_gnl(rest, buffer);
		if (!rest)
			return (gnl_free_and_null(buffer, NULL));
	}
	free(buffer);
	return (rest);
}

static char	*gnl_extract_line(char *rest)
{
	char	*line;
	int		i;
	int		size;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		size = i + 2;
	else
		size = i + 1;
	line = malloc(sizeof(char) * size);
	if (!line)
		return (NULL);
	ft_memcpy(line, rest, i);
	if (rest[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

static char	*gnl_generate_new_rest(char *old_rest)
{
	char	*rest;
	int		i;

	i = 0;
	rest = NULL;
	if (!old_rest)
		return (NULL);
	while (old_rest[i] && old_rest[i] != '\n')
		i++;
	if (old_rest[i] == '\n')
		rest = ft_strdup(old_rest + i + 1);
	free(old_rest);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	rest = gnl_extract_rest(rest, fd);
	if (!rest)
		return (NULL);
	line = gnl_extract_line(rest);
	rest = gnl_generate_new_rest(rest);
	if (!line || !(*line))
		return (gnl_free_and_null(line, rest));
	return (line);
}
