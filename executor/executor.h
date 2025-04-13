/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:09:30 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/13 17:43:29 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef EXECUTOR_H
# define EXECUTOR_H
# include "../parser/parser.h"
# include "../env/env.h"
# include "../libft/libft.h"
# include "../builtins/builtins.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include "../expansion/expansion.h"
#include <termios.h>
/*Executor*/

// volatile	sig_atomic_t	g_signal_recieved = 0;

int     execute_ast(t_msh *msh, t_ast *node);
pid_t   execute_simple_cmd(char *path, char **args, char **env);
int     execute_pipe(t_msh *msh, t_ast *ast);
void    increment_shlvl(t_list *env);

// cmd path utils

char	*get_cmd_path(char *full_cmd, char **env, int *i);
char	**get_args(t_ast *ast);

// free utils

void	free_arr(char **arr);
void    free_env_list(t_list *env);

//signals

void	handle_sig(int sig);

//redirections
int 	process_heredocs(t_ast *ast, t_list *env, int *stop);
void    donothing(int sig);
char	*gen_name();

int	execute(t_msh *msh);
void	ft_close(int *fd);
void close_hds_rec(t_ast *ast);
void	close_hds(t_reds **reds);
int	handle_redirections(t_ast *ast, t_msh *msh);
int	fill_new_hd(int fd, t_reds *red, t_msh *msh);


# endif