/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:43:45 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/13 15:19:33 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "builtins.h"

int ft_pwd(t_msh *msh)
{
	int		i;
	char	*cwd;

	if (!msh->logical_pwd)
		return (ft_printf_error("pwd: error retrieving \
		current directory: getcwd: cannot access parent \
		directories: No such file or directory\n", NULL, NULL, NULL), 1);
	i = 0;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		printf("%s\n", msh->logical_pwd);
	return(0);
}
