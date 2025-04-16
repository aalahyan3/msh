/* ************************************************************************** */
/*                                                                         */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:20:23 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/11 23:19:13 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../executor/executor.h"
# include "../libft/libft.h"

# ifndef INVALID_IDF
#  define INVALID_IDF ": invalid identifier\n"
# endif

int		ft_cd(char **path, t_msh *msh);
int		ft_echo(char **arg);
int		ft_env(t_list *env);
int		ft_export(char **args, t_msh *msh);
int		ft_pwd(t_msh *msh);
int		ft_unset(t_list **env, char **keys);
int		ft_exit(t_msh *msh, char **args);
int		array_size(char **s);
void	clear_msh(t_msh *msh);
void	ft_setenv(char *var, char *value, int defined, t_list **env);
char	*get_from_env(char *var, t_list *env);
int		valid_identifier(char *key);
void	handle_var_without_value(char *var_name, t_list *env);
int		count_env_vars(t_list *ev);
void	fill_env_array(t_list *ev, struct s_env **env_array);
void	sort_env_array(struct s_env **env_array, int count);
void	print_sorted_env(struct s_env **env_array, int count);
char	*inject_quotes(char *str);
void	parse_export_arg(char *arg, t_list *env);
void	append_to_var(char *var_name, char *value, t_list *env);
void	handle_var_with_value(char *var_name, char *value, t_list *env);
int		arr_len(char **arr);


#endif