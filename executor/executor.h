/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:09:30 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/19 17:44:29 by aaitabde         ###   ########.fr       */
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

# ifndef DONE_REDIRECTION
# define DONE_REDIRECTION 2
# endif
# ifndef ERROR_REDIRECTION
# define ERROR_REDIRECTION 1
# endif
# ifndef NO_REDIRECTION
# define NO_REDIRECTION 0
# endif
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
int     ft_env(t_list *env);
int     ft_unset(t_list *env, char **keys);
//signals

void	handle_signals(void);

//redirections 
int 	check_syntax(t_reds **reds);
void	process_heredocs(t_ast *ast, t_list *env);
# endif