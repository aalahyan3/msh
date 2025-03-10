/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:43:44 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/10 14:04:47 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	ft_cd(char *path)
{
	struct stat st;

	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			printf("minishell: %s: Not a directory\n", path);
			return(free_arr(cmd), NULL);
		}
		if (ft_strncmp(path, "..", 2) == 0)
			return (chdir(trim_last_dir()));
		
	}
	ft_printf("minishell: cd: %s: : No such file or directory", path);
	return (1);
}