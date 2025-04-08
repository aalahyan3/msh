/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:34:30 by aaitabde          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/08 22:15:36 by aalahyan         ###   ########.fr       */
=======
/*   Updated: 2025/04/08 21:24:08 by aaitabde         ###   ########.fr       */
>>>>>>> 0bc300aea9f680422e1533f20a2b0daf19bd548b
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
	int 	i;
	int 	index;
	char 	**args;
	char	*buffer;
	char	*temp;

	args = expand(arg, msh);
	i = 1;
	buffer = NULL;
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
<<<<<<< HEAD
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
=======
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if(index == 1)
		write(1, "\n", 1);
>>>>>>> 0bc300aea9f680422e1533f20a2b0daf19bd548b
	free_2d_array(args);
	return (0);
}
