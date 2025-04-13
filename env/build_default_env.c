/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_default_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:37:01 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/13 20:16:14 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_list	*build_default_env(void)
{
	t_list	*env;
	char	*pwd;
	char	*temp;

	temp = getcwd(NULL, 0);
	if (!temp)
		return (NULL);
	pwd = ft_strjoin("PWD=", temp);
	free(temp);
	if (!pwd)
		return (NULL);
	env = NULL;
	ft_lstadd_back(&env, ft_lstnew(make_env_node(pwd)));
	free(pwd);
	ft_lstadd_back(&env, ft_lstnew(make_env_node("SHLVL=1")));
	ft_lstadd_back(&env, ft_lstnew(make_env_node("TERM=xterm")));
	ft_lstadd_back(&env, \
ft_lstnew(make_env_node("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
	return (env);
}
