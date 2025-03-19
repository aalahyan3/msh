/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:21:46 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/19 17:52:06 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	ft_unset(t_list *env, char **keys)
{
	t_list	*tmp;
	t_list	*prev;
	int		i;

	tmp = env;
	prev = NULL;
	i = 1;
	while (keys[i])
	{
		while(tmp)
		{
			if (ft_strncmp(((struct s_env *)tmp->content)->key, keys[i], ft_strlen(keys[i])) == 0)
			{
				printf("keys[%d] == %s\n", i, keys[i]);
				if (prev)
					prev->next = tmp->next;
				else
					env = tmp->next;
				free(tmp->content);
				free(tmp);
				return (0);
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
