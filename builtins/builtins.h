/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:20:23 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/24 07:20:51 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "../executor/executor.h"
# include "../libft/libft.h"

int	ft_cd(char *path);
int ft_echo(char **arg, t_list *env);
int ft_env(t_list *env);
int ft_export(char **args, t_list *env);
int ft_pwd(t_list *envp);
int	ft_unset(t_list *env, char **keys);
int ft_exit(t_msh *msh, char **args);
#endif