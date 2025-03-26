/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:43:44 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/26 04:48:07 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*trim_last_dir(char *cwd)
{
	int		len;

	len = ft_strlen(cwd);
	while (len >= 0)
	{
		printf("len = %d\n", len);
		printf("cwd[len] = %c\n", cwd[len]);
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

void	update_old_pwd(t_msh *msh)
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
			env_tmp->value = get_from_env("PWD", msh->env);
			found = 1;
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

	printf("path = %s\n", path);
	home = get_from_env("HOME", msh->env);
	if (!path)
	{
		if (chdir(home) == -1)
			write(2, "msh: cd: HOME not set\n", 22);
		return (1);
	}
	if (!*path)
		return (update_old_pwd(msh), 1);
	if (ft_strncmp(path, "-\0", 2) == 0)
	{
		old_pwd = get_from_env("OLDPWD", msh->env);
		if (chdir(old_pwd) == -1)
			write(2, "msh: cd: OLDPWD not set\n", 24);
		if (old_pwd)
			ft_printf("%s\n", old_pwd);
		return (0);
	}
	if (ft_strncmp(path, ".\0", 2) == 0)
	{
		update_old_pwd(msh);
		return (0);
	}
	if (ft_strncmp(path, "..\0", 3) == 0)
		return (update_old_pwd(msh), chdir(trim_last_dir(getcwd(NULL, 0))));
	if (ft_strncmp(path, "--\0", 3) == 0 || ft_strncmp(path, "~\0", 2) == 0)
		return (update_old_pwd(msh), chdir(getenv("HOME")));
	if (stat(path, &st) == 0)
	{
		if (S_ISDIR(st.st_mode) == 0)
		{
			printf("msh: %s: Not a directory\n", path);
			return (update_old_pwd(msh), 1);
		}
		else
			return (update_old_pwd(msh), chdir(path));
	}
	ft_printf("msh : cd: %s: : No such file or directory\n", path);
	return (1);
}
