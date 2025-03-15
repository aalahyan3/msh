/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:09:30 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/15 11:34:43 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*Executor*/

int		execute_ast(t_ast *ast, t_list *env);
pid_t	execute_simple_cmd(char *path, char **args, char **env);
int		execute_pipe(t_ast *ast, t_list *env);

// cmd path utils

char	*get_cmd_path(char *full_cmd, char **env, int *i);
char	**get_args(t_ast *ast);

// free utils

void	free_arr(char **arr);

// builtins
int		ft_echo(char **args, char **env);
int		ft_pwd(char **env);
int		ft_cd(char *path);

//signals

void	handle_signals(void);

//redirections 
void	check_syntax(t_reds **reds);
void	process_heredocs(t_ast *ast);
