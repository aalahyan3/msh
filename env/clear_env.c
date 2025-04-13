/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:24:11 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/13 18:36:42 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	free_env(void *content)
{
	struct s_env	*env;

	env = (struct s_env *)content;
	free(env->key);
	free(env->value);
	free(env);
}

void	clear_env(t_list *env_l)
{
	ft_lstclear(&env_l, free_env);
}
