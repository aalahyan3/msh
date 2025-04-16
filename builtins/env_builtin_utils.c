/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:13:14 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/15 22:14:21 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*get_from_env(char *var, t_list *env)
{
	while (env)
	{
		if (ft_strcmp(((struct s_env *)env->content)->key,
				var) == 0)
			return (((struct s_env *)env->content)->value);
		env = env->next;
	}
	return (NULL);
}
