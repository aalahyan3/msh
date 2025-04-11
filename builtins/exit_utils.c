/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:38:04 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/11 15:38:22 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void    clear_msh(t_msh *msh)
{
	clear_env(msh->env);
	free_ast(&msh->ast);
	rl_clear_history();
}

int    array_size(char **s)
{
	int    i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}