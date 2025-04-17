/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:32:47 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/17 10:04:06 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# include "../env/env.h"

enum e_tok_type
{
	NONE,
	PIPE,
	OR,
	AND,
	BLOCK,
	COMMAND,
	REDIRECTIONS,
	SYMBOL_1,
	SYMBOL_2,
	FORBIDDEN,
	WORD
};

enum e_red_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HEREDOC
};

enum e_l_parse
{
	L_NONE,
	L_OR,
	L_AND,
	L_PIPE,
	L_OPEN_P,
	L_CLOSE_P,
	L_SEMICOLON,
	L_AMPERCENT,
	L_REDIRECTION,
	L_WORD
};

typedef struct s_l_parse
{
	char			*content;
	enum e_l_parse	type;
}	t_l_parse;

typedef struct s_reds
{
	char			*file;
	enum e_red_type	type;
	int				fd;
	bool			is_hd;
}	t_reds;

typedef struct s_tok
{
	char			*content;
	enum e_tok_type	type;
}	t_tok;

typedef struct s_ast
{
	char				*content;
	void				*data;
	enum e_tok_type		type;
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

typedef struct s_msh
{
	t_ast		*ast;
	t_list		*env;
	int			last_exit;
	char		*prompt;
	char		*logical_pwd;
	bool		is_child;
}	t_msh;

t_list		*tokenize(char	*prompt);
t_ast		*process_prompt(char *prompt);
void		skip_quotes(char *s, int *i, char c);
void		skip_parentheses(char *s, int *i);
t_ast		*build_ast(t_list *tok_list);
t_ast		*get_redirections(char *s);
t_ast		*expand_block(char *s);
void		free_red_structs(t_reds **reds);
t_ast		*parse(char *prompt);
void		free_ast(t_ast **ast);
bool		initial_checks(char *s);
bool		linear_parsing(char *s);
char		*get_next_cmd(char *s, int *i);
bool		valid_blocks(char *s);
t_l_parse	*get_next_token(char *s, int *i);
char		*get_inside_parenthisis(char *s, int i);
char		*get_next_red(char *s, int *i);
void		ft_printf_error(char *s1, char *s2, char *s3, char *s4);
void		free_2d_array(char **arr);

#endif