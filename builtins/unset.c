/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:21:46 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/24 01:31:38 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
