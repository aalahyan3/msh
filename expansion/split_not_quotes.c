/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_not_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 03:02:29 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/28 20:52:07 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static void	defernciate_command(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if ((str[i] && str[i] == '\'') || str[i] == '"')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
			{
				if (str[i] == ' ')
					str[i] = '\x01';
				if (str[i] == '\t')
					str[i] = '\x02';
				i++;
			}
			continue ;
		}
		i++;
	}
}

static void	redefernciate_command(char	**array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == '\x01')
				array[i][j] = ' ';
			else if (array[i][j] == '\x02')
				array[i][j] = '\t';
			j++;
		}
		i++;
	}
}

char	**split_not_quotes(char *cmd)
{
	char	**array;

	defernciate_command(cmd);
	array = split_msh(cmd);
	if (!array)
		return (NULL);
	if (!array)
		return (NULL);
	redefernciate_command(array);
	free(cmd);
	return (array);
}
