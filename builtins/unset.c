/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:21:46 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/13 20:49:19 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	free_node(t_list *tmp)
{
	free(((struct s_env *)tmp->content)->key);
	free(((struct s_env *)tmp->content)->value);
	free(tmp->content);
	free(tmp);
}

static int	operate(t_list *env, t_list *tmp, t_list *prev, char **key)
{
	if (ft_strncmp(((struct s_env *)tmp->content)->key, \
			*key, ft_strlen(*key)) == 0)
	{
		if (prev)
			prev->next = tmp->next;
		else
			env = tmp->next;
		free_node(tmp);
		return (0);
	}
	return (1);
}

int	ft_unset(t_list *env, char **keys)
{
	t_list	*tmp;
	t_list	*prev;
	int		i;

	if (keys[1] == NULL)
		return (0);
	(1) && (tmp = env, prev = NULL, i = 1);
	while (keys[i])
	{
		if (!valid_identifier(keys[i]))
		{
			ft_printf_error("unset: `", keys[i], "': not a valid identifier\n", \
			NULL);
			i++;
			continue ;
		}
		while (tmp)
		{
			if (!operate(env, tmp, prev, &keys[i]))
				break ;
			(1) && (prev = tmp, tmp = tmp->next);
		}
		(1) && (prev = NULL, tmp = env, i++);
	}
	return (1);
}
