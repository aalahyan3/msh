/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:34:30 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/08 21:24:08 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_for_n_flag(char **arg)
{
	int i;
	size_t n;

	i = 1;
	n = 1;
	while(arg[i] && arg[i][0] == '-' && arg[i][1] == 'n')
	{
		while (arg[i][n] == 'n')
			n++;
		if (arg[i][n] != '\0')
			return (i);
		i++;
	}
	return (i);
}
int ft_echo(char **arg, t_msh *msh)
{
	int i;
	int index;
	char **args;

	args = expand(arg, msh);
	i = 1;
	if (!args[i])
	{
		write(1, "\n", 1);
		free_2d_array(args);
		return (0);
	}
	i = check_for_n_flag(args);
	index = i;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if(index == 1)
		write(1, "\n", 1);
	free_2d_array(args);
	return (0);
}
