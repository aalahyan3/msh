/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:36:07 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/21 22:40:15 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void ft_setenv(char *var, char *value, int defined, t_list **env)
{
	t_list *node = malloc(sizeof(t_list));
	if (!node)
		return;
	struct s_env *new_env = malloc(sizeof(struct s_env));
	if (!new_env)
	{
		free(node);
		return;
	}
	new_env->key = ft_strdup(var);
	new_env->value = ft_strdup(value);
	new_env->defined = defined;
	node->content = new_env;
	node->next = NULL;
	ft_lstadd_back(env, node);
}

int count_env_vars(t_list *ev)
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

void fill_env_array(t_list *ev, struct s_env **env_array)
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

void sort_env_array(struct s_env **env_array, int count)
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
			if (ft_strncmp(env_array[j]->key, env_array[j + 1]->key, ft_strlen(env_array[j + 1]->key)) > 0)
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

void print_sorted_env(struct s_env **env_array, int count)
{
	int i;
	
	i = 0;
	while (i < count)
	{
		write(1, "declare -x ", 11);
		write(1, env_array[i]->key, ft_strlen(env_array[i]->key));
		if (env_array[i]->defined)
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			write(1, env_array[i]->value, ft_strlen(env_array[i]->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}

void ft_env_sorted(t_list *ev)
{
	int				count;
	struct s_env	**env_array;

	count = count_env_vars(ev);
	if (count == 0)
		return ;
	env_array = malloc(sizeof(struct s_env *) * count);
	if (!env_array)
		return ;
	fill_env_array(ev, env_array);
	sort_env_array(env_array, count);
	print_sorted_env(env_array, count);
	free(env_array);
}

int check_for_valid_identifier(char *arg)
{
	int i;
	char *equals_pos;

	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (1);
	equals_pos = ft_strchr(arg, '=');
	equals_pos = '\0';
	i = 1;
	while (arg[i] && (equals_pos == NULL || &arg[i] < equals_pos))
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '$' && arg[i] != '?' && arg[i] != '!' && arg[i] != '*' && arg[i] != '#')
			return (1);
		i++;
	}
	return (0);
}


int find_env_var(t_list *env, char *var_name, struct s_env **found_var)
{
	t_list *current;
	struct s_env *env_var;
	int found;
	
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

void handle_var_with_value(char *var_name, char *value, t_list *env)
{
	struct s_env *existing_var;
	int found;
	
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

void handle_var_without_value(char *var_name, t_list *env)
{
	int found;
	
	found = find_env_var(env, var_name, NULL);
	if (!found)
		ft_setenv(var_name, "", 0, &env);
}

void	inject_quotes(char **str)
{
	int len;
	int i;

	i = 0;
	printf("string before injecting quotes: %s\n", str);
	if (str && *str && *str[0] == '"')
		return ;
	len = ft_strlen(*str);
	char *quoted_str = malloc(len + 3);
	if (!quoted_str)
		return ;
	ft_bzero(quoted_str, len + 3);
	quoted_str[0] = '"';
	ft_memcpy(quoted_str + 1, str, len);
	quoted_str[len + 1] = '"';
	quoted_str[len + 2] = '\0';
	*str = quoted_str;
}

char    *expand_string_without_splitting(char *str, t_list *env)
{
	char	**expanded_str;
	char	*tmp;

	tmp = str;
	inject_quotes(&str);
	if (!str)
		return (NULL);
	expanded_str = expand(&str, env);
	free(str);
	if (!expanded_str)
		return (tmp);
	return (expanded_str[0]);
}

void    expand_value(char **value, t_list *env)
{
	char *expanded_value;;

	expanded_value = expand_string_without_splitting(*value, env);
	printf("expanded_value: %s\n", expanded_value);
	if (expanded_value)
		*value = expanded_value;
}

void parse_export_arg(char *arg, t_list *env)
{
	char	*var;
	char	*value;
	char	*equals_pos;

	var = ft_strdup(arg);
	if (!var)
		return;
	equals_pos = ft_strchr(var, '=');
	if (equals_pos != NULL)
	{
		*equals_pos = '\0';
		value = equals_pos + 1;
		expand_value(&value, env);
		handle_var_with_value(var, value, env);
	}
	else
		handle_var_without_value(var, env);
	free(var);
}

char	**expand_keys(char **args, t_list *env)
{
	int i;

	i = 1;
	while (args[i] != NULL)
	{
		
	}
	return (args);
}

int ft_export(char **args, t_list *env)
{
	int i;
	int ret = 0;

	if (args[1] == NULL)
	{
		ft_env_sorted(env);
		return (0);
	}
	i = 1;
	args = expand_keys(args, env);
	while (args[i] != NULL)
	{
		// if (check_for_valid_identifier(args[i]))
		// {
		// 	write(2, "msh: export: `", 14);
		// 	write(2, args[i], ft_strlen(args[i]));
		// 	write(2, "': not a valid identifier\n", 27);
		// 	ret = 1;
		// }
		// else
		parse_export_arg(args[i], env);
		i++;
	}
	return (ret);
}
