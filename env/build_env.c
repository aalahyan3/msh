/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:22:40 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/12 22:26:59 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*get_key(char *var)
{
	int	size;

	size = 0;
	while (var[size] && var[size] != '=')
		size++;
	return (ft_substr(var, 0, size));
}

struct s_env	*make_env_node(char *var)
{
	char	*key;
	char	*value;
	char	*tmp;
	struct s_env	*env;


	key = get_key(var);
	if (!key)
		return (NULL);
	tmp = ft_strchr(var, '=');
	value = ft_strdup(tmp + 1);
	if (!value)
		return (free(key), NULL);
	env = malloc(sizeof(struct s_env));
	if (!env)
		return (free(key), free(value), NULL);
	env->key = key;
	env->value = value;
	env->defined = true;
	return (env);
}

t_list	*build_env(char **env_array)
{
	t_list	*env;
	int		i;

	i = 0;
	env = NULL;
	while (env_array[i])
	{
		ft_lstadd_back(&env, ft_lstnew(make_env_node(env_array[i])));
		i++;
	}
	return (env);
}
