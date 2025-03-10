/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_path_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 07:57:43 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/10 14:04:26 by aaitabde         ###   ########.fr       */
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

char	*get_cmd_path(char *full_cmd, char **env, int *i)
{
	char	**cmd;
	char	*tmp;
	struct stat st;
	
	cmd = ft_split(full_cmd, ' ');
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd[0], '/'))
	{
		if (stat(cmd[0], &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				printf("minishell: %s: is a directory\n", cmd[0]);
				*i = 0;
				return(free_arr(cmd), NULL);
			}
			if (access(cmd[0], X_OK) == 0)
			{
				tmp = ft_strdup(cmd[0]);
				return(free_arr(cmd), tmp);
			}
			if (access(cmd[0], F_OK) == 0)
			{
				printf("minishell: %s: Permission denied\n", cmd[0]);
				*i = 0;
				return(free_arr(cmd), NULL);
			}
		}
		printf("minishell: %s: No such file or directory\n", cmd[0]);
		*i = 0;
		return(free_arr(cmd), NULL);
	}
	*i = 1;
	return (search_in_path(cmd, env));
}
