/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:47:00 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/13 21:48:11 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	print_sorted_env(struct s_env **env_array, int count)
{
	int				i;
	struct s_env	*current;

	i = 0;
	while (i < count)
	{
		current = env_array[i];
		write(1, "declare -x ", 11);
		write(1, current->key, ft_strlen(current->key));
		if (current->defined)
		{
			if (current->key == NULL || current->value == NULL)
				continue ;
			write(1, "=", 1);
			write(1, "\"", 1);
			write(1, current->value, ft_strlen(current->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

int	find_env_var(t_list *env, char *var_name, struct s_env **found_var)
{
	t_list			*current;
	struct s_env	*env_var;
	int				found;

	current = env;
	found = 0;
	while (current && !found)
	{
		env_var = (struct s_env *)current->content;
		if (ft_strncmp(env_var->key, var_name, ft_strlen(var_name)) == 0)
		{
			if (found_var)
				*found_var = env_var;
			found = 1;
		}
		current = current->next;
	}
	return (found);
}

void	handle_var_with_value(char *var_name, char *value, t_list *env)
{
	struct s_env	*existing_var;
	int				found;

	found = find_env_var(env, var_name, &existing_var);
	if (found)
	{
		free(existing_var->value);
		existing_var->value = ft_strdup(value);
		existing_var->defined = 1;
	}
	else
		ft_setenv(var_name, value, 1, &env);
}

void	handle_var_without_value(char *var_name, t_list *env)
{
	int	found;

	found = find_env_var(env, var_name, NULL);
	if (!found)
		ft_setenv(var_name, "", 0, &env);
}

void	append_to_var(char *var_name, char *value, t_list *env)
{
	struct s_env	*existing_var;
	int				found;
	char			*new_value;

	found = find_env_var(env, var_name, &existing_var);
	if (found)
	{
		new_value = ft_strjoin(existing_var->value, value);
		free(existing_var->value);
		existing_var->value = new_value;
		existing_var->defined = 1;
	}
	else
		ft_setenv(var_name, value, 1, &env);
}
