/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:43:44 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/19 15:32:23 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*trim_last_dir(char *cwd)
{
	int		len;

	len = ft_strlen(cwd);
	while (len >= 0)
	{
		if (cwd[len] == '/')
			break ;
		cwd[len] = '\0';
		len--;
	}
	cwd[len] = '\0';
	return(cwd);
}

int	ft_cd(char *path)
{
	struct stat st;
	char *home;

	home = getenv("HOME");
	if (!path)
	{
		printf("home = %s\n", home);
		int ret = chdir(home);
		printf("chdir return value: %d\n", ret);
		if (ret == -1)
			perror("minishell");
		return (1);
	}
	if (!*path)
		return (1);
	if (ft_strncmp(path, "..", 2) == 0)
		return (chdir(trim_last_dir(getcwd(NULL, 0))));
	if (ft_strncmp(path, "--\0", 3) == 0 || ft_strncmp(path, "~\0", 2) == 0)
		return (chdir(getenv("HOME")));
	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode) == 0)
		{
			printf("minishell: %s: Not a directory\n", path);//old pwd
			return (1);//old pwd
		}//old pwd
		else//old pwd
			return (chdir(path));//old pwd
	}//old pwd
	ft_printf("minishell: cd: %s: : No such file or directory\n", path);
	return (1);
}
