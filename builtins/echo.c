/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:34:30 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/10 09:53:43 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_for_n_flag(char **arg)
{
	int i;
	size_t n;

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
int ft_echo(char **arg, t_msh *msh)
{
	int 	i;
	int 	index;
	char 	**args;
	char	*buffer;
	char	*temp;

	i = 1;
	buffer = NULL;
	args = arg;
	if (!args[i])
	{
		write(1, "\n", 1);
		return (0);
	}
	i = check_for_n_flag(args);
	index = i;
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
	if(index == 1)
	{
		temp = ft_strjoin(buffer, "\n");
		free(buffer);
		buffer = temp;
	}
	ft_putstr_fd(buffer, 1);
	free(buffer);
	return (0);
}
