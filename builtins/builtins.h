/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:20:23 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/11 15:39:07 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "../executor/executor.h"
# include "../libft/libft.h"

int	ft_cd(char *path, t_msh *msh);
int ft_echo(char **arg, t_msh *msh);
int ft_env(t_list *env);
int ft_export(char **args, t_msh *msh);
int ft_pwd(t_list *envp);
int	ft_unset(t_list *env, char **keys);
int ft_exit(t_msh *msh, char **args);

//utils
int    array_size(char **s);
void    clear_msh(t_msh *msh);
void    ft_setenv(char *var, char *value, int defined, t_list **env);
char	*get_from_env(char *var, t_list *env);

#endif