/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:56:01 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/22 16:32:26 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void free_env_list(t_list *env)
{
    t_list *current = env;
    t_list *next;

    while (current)
    {
        next = current->next;
        struct s_env *env_var = (struct s_env *)current->content;
        free(env_var->key);
        free(env_var->value);
        free(env_var);
        free(current);
        current = next;
    }
}
