/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:34:30 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/22 22:00:14 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	check_for_n_flag(char **arg)
{
	int i;
	size_t n;

	i = 1;
	n = 1;
	while(arg[i] && arg[i][0] == '-' && arg[i][1] == 'n')// echo -n -nnnn s -n
	{
		while (arg[i][n] == 'n')
			n++;
		if (arg[i][n] != '\0')
			return (i);
		i++;
	}
	return (i);
}

int ft_echo(char **arg, t_list *env)
{
	int i;
	int index;
	char **args;

	args = expand(arg, env);
	free_2d_array(args);
	return (0);
	i = 1;
	if (!args[i])
	{
		write(1, "\n", 2);
		free_2d_array(args);
		return (0);
	}
	i = check_for_n_flag(args);
	index = i;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if(index == 1)
		write(1, "\n", 2);
	return (0);
}
