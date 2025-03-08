/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:09:30 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/08 11:22:31 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Executer*/

void		execute_ast(t_ast *ast, char **env);
pid_t		execute_simple_cmd(char *path, char **args, char **env);
// cmd path utils
char	*get_cmd_path(char *full_cmd, char **env);

// free utils

void	free_arr(char **arr);

// builtins
int ft_echo(char **args, char **env);