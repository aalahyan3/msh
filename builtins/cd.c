/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:43:44 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/12 13:00:18 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_from_env(char *var, t_list *env)
{
	while (env)
	{
		if (ft_strncmp(((struct s_env *)env->content)->key,
				var, ft_strlen(var)) == 0)
			return (((struct s_env *)env->content)->value);
		env = env->next;
	}
	return (NULL);
}

void	update_env_key(t_list *env, char *key, char *value, int *found)
{
	struct s_env	*env_tmp;

	while (env)
	{
		env_tmp = env->content;
		if (ft_strncmp(env_tmp->key, key, ft_strlen(key) + 1) == 0)
		{
			free(env_tmp->value);
			env_tmp->value = ft_strdup(value);
			*found = 1;
			return ;
		}
		env = env->next;
	}
}

void	update_pwd_env_vars(t_msh *msh, char *old_path)
{
	char	*new_path;
	int		found_old;
	int		found_pwd;

	new_path = getcwd(NULL, 0);
	found_old = 0;
	found_pwd = 0;
	update_env_key(msh->env, "OLDPWD", old_path, &found_old);
	update_env_key(msh->env, "PWD", new_path, &found_pwd);
	if (!found_old)
		ft_setenv("OLDPWD", old_path, 1, &msh->env);
	if (!found_pwd)
		ft_setenv("PWD", new_path, 1, &msh->env);
	free(new_path);
}

static int	cd_dash_case(t_msh *msh, char *old_path)
{
	char	*oldpwd;
	int		ret;

	oldpwd = get_from_env("OLDPWD", msh->env);
	if (!oldpwd)
	{
		ft_printf_error("cd: OLDPWD not set\n", NULL, NULL, NULL);
		free(old_path);
		return (1);
	}
	ret = chdir(oldpwd);
	if (ret == 0)
	{
		printf("%s\n", oldpwd);
		update_pwd_env_vars(msh, old_path);
	}
	free(old_path);
	return (ret);
}

int	ft_cd(char *path, t_msh *msh)
{
	char		*old_path;
	struct stat	st;
	int			ret;

	old_path = getcwd(NULL, 0);
	if (!path || ft_strncmp(path, "~", 2) == 0
		|| ft_strncmp(path, "--", 3) == 0)
		path = get_from_env("HOME", msh->env);
	if (!path)
		return (free(old_path), ft_printf_error("cd: HOME not set\n",
				NULL, NULL, NULL), 1);
	if (ft_strncmp(path, "-", 2) == 0)
		return (cd_dash_case(msh, old_path));
	if (ft_strncmp(path, "..", 3) == 0 || ft_strncmp(path, ".", 2) == 0)
	{
		ret = chdir(path);
		if (ret == 0)
			update_pwd_env_vars(msh, old_path);
		return (free(old_path), ret);
	}
	if (stat(path, &st) != 0 || !S_ISDIR(st.st_mode))
		return (free(old_path), ft_printf_error(path, ": ",
				"No such file or directory\n", NULL), 1);
	ret = chdir(path);
	if (ret == 0)
		update_pwd_env_vars(msh, old_path);
	return (free(old_path), ret);
}
