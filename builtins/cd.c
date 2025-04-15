/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:43:44 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/15 22:14:13 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static	void	update_env_key(t_msh *msh, char *key, char *value, int *found)
{
	t_list			*env;
	struct s_env	*env_tmp;

	env = msh->env;
	while (env)
	{
		env_tmp = env->content;
		if (ft_strcmp(env_tmp->key, key) == 0)
		{
			free(env_tmp->value);
			env_tmp->value = ft_strdup(value);
			*found = 1;
			return ;
		}
		env = env->next;
	}
}

static void	handle_pwd_update(t_msh *msh, char *old_path, char *new_path)
{
	int	found[2];

	(1) && (found[0] = 0, found[1] = 0);
	update_env_key(msh, "OLDPWD", msh->logical_pwd, &found[0]);
	update_env_key(msh, "PWD", new_path, &found[1]);
	free(msh->logical_pwd);
	msh->logical_pwd = getcwd(NULL, 0);
	if (!found[0])
		ft_setenv("OLDPWD", old_path, 1, &msh->env);
	if (!found[1])
		ft_setenv("PWD", new_path, 1, &msh->env);
}

static int	handle_cd_errors(char *path, char *old_path)
{
	struct stat	st;

	if (chdir(path) != 0)
	{
		if (stat(path, &st) != 0 || !S_ISDIR(st.st_mode))
		{
			free(old_path);
			return (ft_printf_error(path, ": ",
					"No such file or directory\n", NULL), 1);
		}
		free(old_path);
		return (1);
	}
	return (0);
}

static int	handle_getcwd_error(t_msh *msh, char *old_path)
{
	char	*new_path;

	ft_printf_error("cd: error retrieving current directory: getcwd: ",
		"cannot access parent directories: No such file or directory\n",
		NULL, NULL);
	new_path = msh->logical_pwd;
	msh->logical_pwd = ft_strjoin(new_path, "/..");
	free(new_path);
	free(old_path);
	return (1);
}

int	ft_cd(char **path, t_msh *msh)
{
	char	*old_path;
	char	*new_path;

	if (path && path[0] && path[1] != NULL)
		return (ft_printf_error("cd: too many arguments\n", \
		NULL, NULL, NULL), 1);
	if (*path && ft_strcmp(*path, ".") == 0)
		return (0);
	old_path = getcwd(NULL, 0);
	if (!*path || ft_strcmp(*path, "~") == 0
		|| ft_strcmp(*path, "--") == 0)
		*path = get_from_env("HOME", msh->env);
	if (!*path)
	{
		free(old_path);
		return (ft_printf_error("cd: HOME not set\n", \
		NULL, NULL, NULL), 1);
	}
	if (handle_cd_errors(*path, old_path))
		return (1);
	new_path = getcwd(NULL, 0);
	if (!new_path)
		return (handle_getcwd_error(msh, old_path));
	handle_pwd_update(msh, old_path, new_path);
	return (free(old_path), free(new_path), 0);
}
