/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:06:59 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/24 01:31:29 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int ft_env(t_list *env)
{
    t_list *tmp;

    tmp = env;
    while(tmp)
    {
        if (((struct s_env *)tmp->content)->value && ft_strncmp(((struct s_env *)tmp->content)->value, "", 1) != 0)
        {
            printf("%s", ((struct s_env *)tmp->content)->key);
            printf("=");
            printf("%s\n", ((struct s_env *)tmp->content)->value);
        }
        tmp = tmp->next;
    }
}
