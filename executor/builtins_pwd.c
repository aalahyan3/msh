/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:43:45 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/09 17:32:13 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int ft_pwd(char **env)
{
	int		i;
	char	*cwd;
	
	i = 0;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		return (0);
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			write(1, env[i] + 4, ft_strlen(env[i] + 4));
			write(1, "\n", 1);
			return (0);
		}
		i++;
	}
	return(1);
}
