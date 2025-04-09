/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:19:14 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/09 15:48:43 by aalahyan         ###   ########.fr       */
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
struct s_env	*make_env_node(char *var);
t_list	*build_default_env(void);
t_list	*build_env(char **env_array);
void	clear_env(t_list *env_l);
char	**make_env(t_list *ev);
#endif