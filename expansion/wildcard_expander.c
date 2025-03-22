/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:12:46 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/22 02:43:34 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "expansion.h"

# include "expansion.h"

int is_match(char *exp, char *name)
{
    // Base case: both strings are empty, match
    if (*exp == '\0' && *name == '\0')
        return 1;

    // Base case: pattern is empty but string is not, no match
    if (*exp == '\0')
        return 0;

    // Base case: string is empty but pattern still has parts, no match
    if (*name == '\0')
    {
        // Only a trailing '*' in the pattern can match the remaining string
        while (*exp == WILDCARD_PACEHOLDER) 
            exp++;  // Skip over '*' characters
        return (*exp == '\0');  // If we reached the end of the pattern, it matches
    }
    // If the current character in the pattern is '*', we try two possibilities:
    if (*exp == WILDCARD_PACEHOLDER)
    {
        // Case 1: Match zero characters (skip '*' and move to the next part of the pattern)
        if (is_match(exp + 1, name)) 
            return 1;

        // Case 2: Match one or more characters (move to the next character in the string)
        if (is_match(exp, name + 1))
            return 1;
    }

    // If the characters match, continue recursively
    if (*exp == *name)
        return is_match(exp + 1, name + 1);

    // No match found
    return 0;
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
		if (is_match(exp, entry->d_name))
			size++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (size);
}

char	*get_next_match(DIR	*dir, char *exp)
{
	struct dirent	*entry;
	entry = readdir(dir);
	while (entry)
	{
		if (is_match(exp, entry->d_name))
			return (ft_strdup(entry->d_name));
		entry = readdir(dir);
	}
	return (NULL);
}

static void	optimize_wildcard_exp(char **exp)
{
	char			*ptr;
	char			*new;

	ptr = ft_strrchr(*exp, '/');
	if (ptr)
	{
		new = ft_strdup(ptr + 1);
		free(*exp);
		*exp = new;
	}
}

char	**wildcard_expander(char *exp)
{
	char	*no_quotes;
	char	**arr;
	DIR		*dir;
	int		i;
	char	*match;

	no_quotes = expand_quotes(exp);
	if (!no_quotes)
		return (NULL);
	optimize_wildcard_exp(&no_quotes);
	dir = opendir(".");
	if (!dir)
		return (free(no_quotes),NULL);
	i = get_size(no_quotes);
	if (!i)
		return (closedir(dir), free(no_quotes), no_match_case(exp));
	arr = malloc((i + 1) * (sizeof(char *)));
	if (!arr)
		return (closedir(dir), free(no_quotes), NULL);
	match = get_next_match(dir, no_quotes);
	i = 0;
	while (match)
	{
		arr[i] = match;
		i++;
		match = get_next_match(dir, no_quotes);
	}
	arr[i] = NULL;
	closedir(dir);
	free(no_quotes);
	return (arr);
}
