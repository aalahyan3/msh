/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 07:57:43 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/13 17:54:03 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr && !*arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

static int	get_path_index(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (0);
	return (i);
}

static char	*search_in_path(char *full_cmd, char **env)
{
	char	**paths;
	char	*path_cmd;
	char	*tmp;
	int		i;

	i = get_path_index(env);
	if (i == 0)
		return (NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin(tmp, full_cmd);
		free(tmp);
		if (access(path_cmd, X_OK) == 0)
			return (free_arr(paths), path_cmd);
		free(path_cmd);
	}
	free_arr(paths);
	return (NULL);
}

char	*get_cmd_path(char *full_cmd, char **env, int *i)
{
	char		*tmp;
	struct stat	st;

	if (!full_cmd)
		return (NULL);
	if (ft_strchr(full_cmd, '/'))
	{
		if (stat(full_cmd, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				printf("msh: %s: is a directory\n", full_cmd);
				return (NULL);
			}
			else
				return (ft_strdup(full_cmd));
		}
		write(2, "msh: ", 6);
		write(2, full_cmd, ft_strlen(full_cmd));
		write(2, ": No such file or directory\n", 28);
		return (NULL);
	}
	*i = 1;
	return (search_in_path(full_cmd, env));
}
