/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:06:59 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/18 17:20:48 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int ft_env(t_list *env)
{
    t_list *tmp;

    tmp = env;
    while(tmp)
    {
        printf("%s", ((struct s_env *)tmp->content)->key);
        printf("=");
        printf("%s\n", ((struct s_env *)tmp->content)->value);
        tmp = tmp->next;
    }
}
