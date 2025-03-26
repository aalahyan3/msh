/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:19:14 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/26 06:10:22 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>
# include "../libft/libft.h"
struct s_env
{
	char	*key;
	char	*value;
	bool	defined;
};


void ft_setenv(char *var, char *value, int defined, t_list **env);
t_list	*build_env(char **env_array);
void	clear_env(t_list *env_l);
char	**make_env(t_list *ev);
#endif