/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 07:57:43 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/08 08:44:17 by aaitabde         ###   ########.fr       */
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


char	*check_direct_path(char **cmd)
{
	char	*tmp;

	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], X_OK) == 0)
		{
			tmp = ft_strdup(cmd[0]);
			free_arr(cmd);
			return (tmp);
		}
		return (NULL);
	}
	return (NULL);
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

static char	*search_in_path(char **cmd, char **env)
{
	char	**paths;
	char	*path_cmd;
	char	*tmp;
	int		i;

	i = get_path_index(env);
	if (i == 0)
		return (free_arr(cmd), NULL);
	paths = ft_split(env[i] + 5, ':');
	if (!paths)
		return (free_arr(cmd), NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path_cmd = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path_cmd, X_OK) == 0)
			return (free_arr(cmd), free_arr(paths), path_cmd);
		free(path_cmd);
	}
	free_arr(paths);
	free_arr(cmd);
	return (NULL);
}

char	*get_cmd_path(char *full_cmd, char **env)
{
	char	**cmd;
	char	*tmp;

	cmd = ft_split(full_cmd, ' ');
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd[0], '/'))
	{
		if (access(cmd[0], X_OK) == 0)
		{
			tmp = ft_strdup(cmd[0]);
			free_arr(cmd);
			return (tmp);
		}
		free_arr(cmd);
		return (NULL);
	}
	return (search_in_path(cmd, env));
}
