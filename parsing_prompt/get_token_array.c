/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 00:17:31 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/03 00:35:58 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	defernciate_command(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
			{
				if (str[i] == ' ')
					str[i] = 1;
				if (str[i] == '\t')
					str[i] = 2;
				i++;
			}
		}
		if (str[i] && str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
			{
				if (str[i] == ' ')
					str[i] = 1;
				else if (str[i] == '\t')
					str[i] = 2;
				i++;
			}
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
			if (array[i][j] == 1)
				array[i][j] = ' ';
			else if (array[i][j] == 2)
				array[i][j] = '\t';
			j++;
		}
		i++;
	}
}

char	**get_token_array(char *cmd)
{
	char	**array;

	defernciate_command(cmd);
	array = ft_split_msh(cmd);
	if (!array)
		return (NULL);
	redefernciate_command(array);
	return (array);
}
