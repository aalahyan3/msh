/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:43:45 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/26 05:08:27 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"

int ft_pwd(t_list *envp)
{
	int		i;
	char	*cwd;
	char	**env;

	env = make_env(envp);
	i = 0;
	cwd = get_from_env("PWD", envp);
	if (cwd)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		free_arr(env);
		return (0);
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			write(1, env[i] + 4, ft_strlen(env[i] + 4));
			write(1, "\n", 1);
			free_arr(env);
			return (0);
		}
		i++;
	}
	free_arr(env);
	return(1);
}
