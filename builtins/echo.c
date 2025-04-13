/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:34:30 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/13 20:58:14 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_for_n_flag(char **arg)
{
	int		i;
	size_t	n;

	i = 1;
	n = 1;
	while (arg[i] && arg[i][0] == '-' && arg[i][1] == 'n')
	{
		while (arg[i][n] == 'n')
			n++;
		if (arg[i][n] != '\0')
			return (i);
		i++;
	}
	return (i);
}

static int	check_option(char **args, char **buffer, int *i, int *index)
{
	*i = 1;
	*buffer = NULL;
	if (!args[*i])
	{
		write(1, "\n", 1);
		return (0);
	}
	*i = check_for_n_flag(args);
	*index = *i;
	return (1);
}

int	ft_echo(char **args, t_msh *msh)
{
	int		i;
	int		index;
	char	*buffer;
	char	*temp;

	if (check_option(args, &buffer, &i, &index) == 0)
		return (0);
	while (args[i])
	{
		temp = ft_strjoin(buffer, args[i]);
		free(buffer);
		buffer = temp;
		if (args[i + 1])
		{
			temp = ft_strjoin(buffer, " ");
			free(buffer);
			buffer = temp;
		}
		i++;
	}
	if (index == 1)
		(1) && (temp = ft_strjoin(buffer, "\n"), free(buffer), buffer = temp);
	return (ft_putstr_fd(buffer, 1), free(buffer), 0);
}
