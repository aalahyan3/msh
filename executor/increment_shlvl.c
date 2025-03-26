/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_shlvl.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 05:27:59 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/26 05:38:34 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void increment_shlvl(t_list *env)
{
	char	*shlvl;
	char	*new_shlvl;
	int		lvl;

	shlvl = get_from_env("SHLVL", env);
	if (!shlvl)
	{
		ft_setenv("SHLVL", "1", 1, &env);
		return ;
	}
	if (ft_atoi(shlvl) < 0)
	{
		ft_setenv("SHLVL", "0", 1, &env);
		return ;
	}
	if (ft_atoi(shlvl) >= 999)
	{
		ft_setenv("SHLVL", "", 1, &env);
		return ;
	}
	lvl = ft_atoi(shlvl);
	new_shlvl = ft_itoa(lvl + 1);
	ft_setenv("SHLVL", new_shlvl, 1, &env);
	free(new_shlvl);
}
