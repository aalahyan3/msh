/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:53:51 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/16 22:12:13 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../env/env.h"
# include "../parser/parser.h"
# include <dirent.h>
# define WILDCARD_PACEHOLDER '\x1'
# define DQUOTE_PACEHOLDER '\x3'
# define SQUOTE_PACEHOLDER '\x4'

typedef struct s_args
{
	char	*arg;
	bool	*quoted;
}	t_args;

char	**expand_vars(char **old, t_msh *msh);

char	**expand(char **arr, t_msh *msh, int export);
char	**split_by_quotes(char *s);
char	**split_not_quotes(char *cmd);
char	**split_msh(char const *s);
char	**expand_wildcards(char	**arr, int export);
char	*expand_quotes(char *s);
char	*find_in_env(char *key, t_list *env);
char	*expand_here_doc(char *line, t_msh *msh);
char	**expand_string(char *str, t_msh *msh);
char	**join_and_split(char **arr);
char	**wildcard_expander(char *exp);
char	**no_match_case(char *s);
char	**expand_string_2(char *str, int export);
char	**triple_to_double(char ***triple);
void	free_triple_array(char ***ar);
char	**expand_filename(char *name, t_msh *msh);
char	*get_var_name(char *s, int *i);
void	optimize_wildcard_exp(char **exp);
void	sort_array(char **arr);
char	*expand_quotes_str(char *str);
void	alter_var_value(char *var_value);

#endif