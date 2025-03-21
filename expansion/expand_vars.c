/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:52:33 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/21 13:53:05 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int get_size(char **a)
{
	int i;

	i = 0;
	while (a[i])
		i++;
	return (i + 1);
}
static	int	get_size_2(char ***tr)
{
	int	size;
	int	i;
	int	j;

	i = 0;
	while (tr[i])
	{
		j = 0;
		while (tr[i][j])
		{
			j++;
			size++;
		}
		i++;
	}
	return (size + 1);
}

static void	free_triple_array(char ***ar)
{
	int	i;

	i = 0;
	while (ar[i])
	{
		free_2d_array(ar[i]);
		i++;
	}
	ar = NULL;
}


char	**triple_to_double(char ***triple)
{
	char	**new;
	int		i;
	int		j;
	int		k;

	new = malloc(sizeof(char *) * get_size_2(triple));
	if (!new)
		free_triple_array(triple);
	i = -1;
	k = 0;
	while (triple[++i])
	{
		j = -1;
		while (triple[i][++j])
			new[k++] = triple[i][j];
	}
	new[k] = NULL;
	return (new);
}

char	**expand_vars(char **old, t_list *env_l)
{
	char	***triple;
	char	**expanded_string;
	int		i;
	int		j;

	triple = malloc(sizeof(char **) * get_size(old));
	if (!triple)
		return (NULL);
	i = -1;
	j = 0;
	while (old[++i])
	{
		expanded_string = expand_string(old[i], env_l);
		if (!expanded_string)
			continue ;
		triple[j++] = expanded_string;
	}
	triple[j] = NULL;
	return (triple_to_double(triple));
}
