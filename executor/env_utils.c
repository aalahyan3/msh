/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:08:30 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/15 13:51:11 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**make_env(t_list *ev)
{
	int		i;
	char	**env;
	char	*tmp;
	char	*tmp1;

	if (!ev)
		return (NULL);
	i = 0;
	env = (char **)malloc((ft_lstsize(ev) + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	while (ev)
	{
		tmp = ft_strjoin(((struct s_env *)(ev->content))->key, "=");
		if (!tmp)
			return (free_arr(env), NULL);
		tmp1 = ft_strjoin(tmp, ((struct s_env *)(ev->content))->value);
		if (!tmp1)
			return (free_arr(env), NULL);
		free(tmp);
		(1) && (env[i] = tmp1, ev = ev->next);
		i++;
	}
	env[i] = NULL;
	return (env);
}
