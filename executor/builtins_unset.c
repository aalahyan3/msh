/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:21:46 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/23 17:26:58 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	ft_unset(t_list *env, char **keys)
{
	t_list	*tmp;
	t_list	*prev;
	int		i;

	if (keys[1] == NULL)
		return (0);
	tmp = env;
	prev = NULL;
	i = 1;
	while (keys[i])
	{
		while(tmp)
		{
			if (ft_strncmp(((struct s_env *)tmp->content)->key, keys[i], ft_strlen(keys[i])) == 0)
			{
				if (prev)
					prev->next = tmp->next;
				else
					env = tmp->next;
				free(((struct s_env *)tmp->content)->key);
				free(((struct s_env *)tmp->content)->value);
				free(tmp->content);
				free(tmp);
				break;
			}
			prev = tmp;
			tmp = tmp->next;
		}
		prev = NULL;
		tmp = env;
		i++;
	}
	return (1);
}
