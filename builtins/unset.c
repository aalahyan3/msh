/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:21:46 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/15 14:00:00 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	free_node(t_list *node)
{
	struct s_env	*env;

	if (!node)
		return ;
	env = (struct s_env *)node->content;
	free(env->key);
	free(env->value);
	free(env);
	free(node);
}

void	remove_node(t_list **env, t_list *node, t_list *prev)
{
	if (!node)
		return ;
	if (prev)
		prev->next = node->next;
	else
		*env = node->next;
	free_node(node);
}

void	remove_matching_env(t_list **env, char *key, t_list **prev)
{
	t_list			*tmp;
	struct s_env	*env_data;

	tmp = *env;
	*prev = NULL;
	while (tmp)
	{
		env_data = (struct s_env *)tmp->content;
		if (ft_strcmp(env_data->key, key) == 0)
		{
			remove_node(env, tmp, *prev);
			break ;
		}
		*prev = tmp;
		tmp = tmp->next;
	}
}

int	process_unset_keys(t_list **env, char **keys, int *status)
{
	int		i;
	t_list	*prev;

	i = 0;
	while (keys[i])
	{
		if (!valid_identifier(keys[i]))
		{
			ft_printf_error("unset: `", keys[i], INVALID_IDF, NULL);
			*status = 1;
			i++;
			continue ;
		}
		remove_matching_env(env, keys[i], &prev);
		i++;
	}
	return (*status);
}

int	ft_unset(t_list **env, char **keys)
{
	int	status;

	if (!env || !*env || !keys || !*keys)
		return (1);
	status = 0;
	return (process_unset_keys(env, keys, &status));
}
