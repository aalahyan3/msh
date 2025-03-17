/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_join.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 02:58:15 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/17 03:24:49 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "expansion.h"

static int get_size(char **a)
{
	int i;

	i = 0;
	while (a[i])
		i++;
	return (i + 1);
}

int	get_size_2(char ***s)
{
	int	i;
	int	size;
	int	j;

	size = 0;
	i = 0;
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			j++;
			size++;
		}
		i++;
	}
	return (size + 1);
}

void	free_triple_array(char ***s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free_2d_array(s[i]);
		i++;
	}
}

char	**join_arrays(char ***triple)
{
	char	**new;
	int		i;
	int		j;
	int		k;

	new = malloc(sizeof(char *) * get_size_2(triple));
	if (!new)
		return (free_triple_array(triple), NULL);
	i = 0;
	k = 0;
	while (triple[i])
	{
		j = 0;
		while (triple[i][j])
		{
			new[k++] = triple[i][j];
			j++;
		}
		i++;
	}
	new[k] = NULL;
	return (new);
}

char	**split_and_join(char **arr)
{
	char	***triple_arr;
	int		i;
	char	**joined;

	triple_arr = malloc(sizeof(char **) * get_size(arr));
	if (!triple_arr)
		return (free_2d_array(arr), NULL);
	i = 0;
	while (arr[i])
	{
		triple_arr[i] = split_not_quotes(arr[i]);
		free(arr[i]);
		i++;
	}
	triple_arr[i] = NULL;
	free(arr);
	return (join_arrays(triple_arr));
}