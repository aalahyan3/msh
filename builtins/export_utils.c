/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:45:42 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/13 21:50:50 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

bool	alter_existing_var(char *var, char *val, int defined, t_list **env)
{
	t_list			*curr;
	struct s_env	*node;
	int				varlen;

	curr = *env;
	varlen = ft_strlen(var);
	while (curr)
	{
		node = curr->content;
		if (!ft_strncmp(var, node->key, varlen) \
		&& varlen == ft_strlen(node->key))
		{
			free(node->value);
			node->value = ft_strdup(val);
			return (true);
		}
		curr = curr->next;
	}
	return (false);
}

void	ft_setenv(char *var, char *value, int defined, t_list **env)
{
	t_list			*node;
	struct s_env	*new_env;

	if (alter_existing_var(var, value, defined, env))
		return ;
	node = malloc(sizeof(t_list));
	if (!node)
		return ;
	new_env = malloc(sizeof(struct s_env));
	if (!new_env)
	{
		free(node);
		return ;
	}
	new_env->key = ft_strdup(var);
	new_env->value = ft_strdup(value);
	new_env->defined = defined;
	node->content = new_env;
	node->next = NULL;
	ft_lstadd_back(env, node);
}

int	count_env_vars(t_list *ev)
{
	int		count;
	t_list	*current;

	count = 0;
	current = ev;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

void	fill_env_array(t_list *ev, struct s_env **env_array)
{
	int		i;
	t_list	*current;

	i = 0;
	current = ev;
	while (current)
	{
		env_array[i] = (struct s_env *)current->content;
		i++;
		current = current->next;
	}
}

void	sort_env_array(struct s_env **env_array, int count)
{
	int				i;
	int				j;
	struct s_env	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strncmp(env_array[j]->key, env_array[j + 1]->key,
					ft_strlen(env_array[j + 1]->key)) > 0)
			{
				temp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
