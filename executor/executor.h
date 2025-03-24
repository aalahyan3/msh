/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:09:30 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/24 00:57:12 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../parser/parser.h"
# include "../env/env.h"
# include "../libft/libft.h"

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>


/*Executor*/

int		execute_ast(t_ast *ast, t_list *env);
pid_t	execute_simple_cmd(char *path, char **args, char **env);
int		execute_pipe(t_ast *ast, t_list *env);

// cmd path utils

char	*get_cmd_path(char *full_cmd, char **env, int *i);
char	**get_args(t_ast *ast);

// free utils

void	free_arr(char **arr);
void    free_env_list(t_list *env);
// builtins
int		ft_echo(char **args, t_list *env);
int		ft_pwd(t_list *env);
int		ft_cd(char *path);
int     ft_env(t_list *env);
int     ft_unset(t_list *env, char **keys);
int     ft_export(char **args, t_list *env);
//signals

void	handle_sig(int sig);

//redirections
int 	check_syntax(t_reds **reds);
void	process_heredocs(t_ast *ast, t_list *env);
void    donothing(int sig);



# endif