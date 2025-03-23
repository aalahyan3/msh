/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 21:40:20 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/23 17:32:18 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_UTILS_H
# define FREE_UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../env/env.h"

void	free_2d_array(char **arr);
void    free_env_list(t_list *env);
#endif
