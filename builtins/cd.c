/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:43:44 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/26 05:17:48 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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

char	*get_from_env(char *var, t_list *env)
{
	while (env)
	{
		if (ft_strncmp(((struct s_env *)env->content)->key, var, ft_strlen(var)) == 0)
			return (((struct s_env *)env->content)->value);
		env = env->next;
	}
	return (NULL);
}

void	update_old_and_new_pwd(t_msh *msh)
{
	struct s_env	*env_tmp;
	struct s_env	*new_env;
	t_list			*env;
	int 			found;
	char			*old_pwd;

	found = 0;
	env = msh->env;
	while(env)
	{
		env_tmp = env->content;
		if (ft_strncmp(env_tmp->key, "OLDPWD\0", 7) == 0)
		{
			free(env_tmp->value);
			env_tmp->value = ft_strdup (get_from_env("PWD", msh->env));
			found = 1;
		}
		if (ft_strncmp(env_tmp->key, "PWD\0", 4) == 0)
		{
			free(env_tmp->value);
			env_tmp->value = getcwd(NULL, 0);
		}
		env = env->next;
	}
	if (!found)
	{
		old_pwd = ft_strdup(get_from_env("PWD", msh->env));
		ft_setenv("OLDPWD", old_pwd, 1, &msh->env);
		free(old_pwd);
	}
}

int	ft_cd(char *path, t_msh *msh)
{
	struct	stat st;
	char	*home;
	char	*old_pwd;
	int		ret;

	home = get_from_env("HOME", msh->env);
	if (!path)
	{
		if (chdir(home) == -1)
			write(2, "msh: cd: HOME not set\n", 22);
		return (1);
	}
	if (!*path)
		return (update_old_and_new_pwd(msh), 1);
	if (ft_strncmp(path, "-\0", 2) == 0)
	{
		old_pwd = get_from_env("OLDPWD", msh->env);
		ret = chdir(old_pwd);
		if (ret == -1)
			write(2, "msh: cd: OLDPWD not set\n", 24);
		else
			update_old_and_new_pwd(msh);
		if (old_pwd)
			ft_printf("%s\n", old_pwd);
		return (0);
	}
	if (ft_strncmp(path, ".\0", 2) == 0)
	{
		update_old_and_new_pwd(msh);
		return (0);
	}
	if (ft_strncmp(path, "..\0", 3) == 0)
	{
		ret = chdir(trim_last_dir(get_from_env("PWD", msh->env)));
		return (update_old_and_new_pwd(msh), ret);
	}
	if (ft_strncmp(path, "--\0", 3) == 0 || ft_strncmp(path, "~\0", 2) == 0)
	{
		ret = chdir(home);
		return (update_old_and_new_pwd(msh), ret);
	}
	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode) == 0)
		{
			printf("msh: %s: Not a directory\n", path);
			return (update_old_and_new_pwd(msh), 1);
		}
		else
		{
			ret = chdir(path);
			return (update_old_and_new_pwd(msh), ret);
		}
	}
	ft_printf("msh : cd: %s: : No such file or directory\n", path);
	return (1);
}
