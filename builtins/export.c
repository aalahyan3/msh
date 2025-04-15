/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:36:07 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/15 14:02:35 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env_sorted(t_list *ev)
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

void	proper_export_expansion(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (valid_identifier(args[i]))
			inject_quotes(&args[i]);
		if (!args[i])
			return ;
		i++;
	}
}

int	ft_export(char **args, t_msh *msh)
{
	int	i;
	int	status;

	if (!msh->env)
		return (1);
	proper_export_expansion(args);
	i = 1;
	status = 0;
	args = expand(args, msh);
	if (args[1] == NULL)
		ft_env_sorted(msh->env);
	while (args[i] != NULL)
	{
		if (!valid_identifier(args[i]))
		{
			ft_printf_error("export: `", args[i], \
			"': not a valid identifier\n", NULL);
			status = 1;
		}
		else
			parse_export_arg(args[i], msh->env);
		i++;
	}
	free_arr(args);
	return (status);
}
