/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:32:47 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/18 23:11:43 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "../ft_func/ft_func.h"
# include "../env/env.h"
# include "../free_utils/free_utils.h"
# include "../expansion/expansion.h"

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



typedef struct s_reds
{
	char		*file;
	enum e_red_type	type;
	int				fd;
}	t_reds;

typedef struct s_tok
{
	char			*content;
	enum e_tok_type	type;
}	t_tok;

typedef struct s_ast
{
	char			*content;
	void			*data;
	enum e_tok_type	type;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

t_list	*tokenize(char	*prompt);
t_ast	*process_prompt(char *prompt, t_list *env);
void	skip_quotes(char *s, int *i, char c);
void	skip_parentheses(char *s, int *i);
t_ast	*build_ast(t_list *tok_list);
void 	ast_vis(t_ast *node, int depth, char *prefix);////////////////!!!!!!!!!
t_ast	*get_redirections(char *s);
t_ast	*expand_block(char *s);
void	free_red_structs(t_reds **reds);
t_ast	*parse(char *prompt, t_list *env_l);
void    free_ast(t_ast *ast);
bool	initial_checks(char *s);
bool	linear_parsing(char *s);


#endif