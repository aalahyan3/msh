/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:12:46 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/17 10:01:15 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int	is_match(char *exp, char *name)
{
	if (*exp == '\0' && *name == '\0')
		return (1);
	if (*exp == '\0')
		return (0);
	if (*name == '\0')
	{
		while (*exp == WILDCARD_PACEHOLDER)
			exp++;
		return (*exp == '\0');
	}
	if (*exp == WILDCARD_PACEHOLDER)
	{
		if (is_match(exp + 1, name))
			return (1);
		if (is_match(exp, name + 1))
			return (1);
	}
	if (*exp == *name)
		return (is_match(exp + 1, name + 1));
	return (0);
}

static int	get_size(char *exp)
{
	DIR				*dir;
	int				size;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return (0);
	size = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (*entry->d_name == '.' && *exp != *entry->d_name)
		{
			entry = readdir(dir);
			continue ;
		}
		if (is_match(exp, entry->d_name))
			size++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (size);
}

static char	*get_next_match(DIR	*dir, char *exp, bool include_hidden)
{
	struct dirent	*entry;

	entry = (void *)0x1;
	while (entry)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (*entry->d_name == '.' && !include_hidden)
			continue ;
		if (is_match(exp, entry->d_name))
			return (ft_strdup(entry->d_name));
	}
	return (NULL);
}

static char	**fill_match_array(char	*exp, int size)
{
	char	**arr;
	int		i;
	char	*match;
	DIR		*dir;

	dir = opendir(".");
	if (!dir)
		return (free(exp), NULL);
	arr = malloc(sizeof(char *) * size);
	if (!arr)
		return (closedir(dir), free(exp), NULL);
	i = 0;
	match = get_next_match(dir, exp, *exp == '.');
	while (match)
	{
		arr[i] = match;
		i++;
		match = get_next_match(dir, exp, *exp == '.');
	}
	arr[i] = NULL;
	closedir(dir);
	free(exp);
	sort_array(arr);
	return (arr);
}

char	**wildcard_expander(char *exp)
{
	char	*no_quotes;
	int		size;

	no_quotes = expand_quotes(exp);
	if (!no_quotes)
		return (NULL);
	optimize_wildcard_exp(&no_quotes);
	size = get_size(no_quotes);
	if (!size)
		return (free(no_quotes), no_match_case(exp));
	return (fill_match_array(no_quotes, size + 1));
}
