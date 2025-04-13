/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:43:45 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/13 13:43:40 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"

int ft_pwd(t_msh *msh, t_list *envp)
{
	int		i;
	char	*cwd;
	char	**env;

	if (!msh->logical_pwd)
		return (ft_printf_error("pwd: error retrieving \
		current directory: getcwd: cannot access parent \
		directories: No such file or directory\n", NULL, NULL, NULL), 1);
	env = make_env(envp);
	i = 0;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		free(cwd);
		free_arr(env);
		return (0);
	}
	else
		cwd = msh->logical_pwd;
	free_arr(env);
	return(1);
}
