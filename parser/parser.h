/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:27:32 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/12 21:42:12 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../env/env.h"
# include "../free_utils/free_utils.h"

enum e_token
{
	NONE,
	BLOCK,
	PIPE,
	WORD,
	WORD_SQ,
	WORD_DQ,
	REDIRECT_IN,
	REDIRECT_OUT,
	AND,
	OR,
	WILD_CARD,
	COMMAND
};

enum e_red_type
{
	INPUT,
	OUTPUT,
	APPEND,
	HERE_DOC
};


typedef struct s_cmd_tok
{
	char	*str;
	int		*quotes;
}	t_cmd_tok;


typedef struct s_red
{
	char			*name;
	enum e_red_type type; // INPU
}	t_red;

typedef struct s_reds
{
	t_red **red;
}	t_reds;

typedef struct s_token
{
	char				*value;
	enum e_token		key;
}	t_token;

typedef struct s_ast
{
	t_token				*token;
	void				*data;
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

int		get_word(t_token **token, char *input, int *i);
t_list	*tokenizer(char *input);
char	*get_block(char *input, int *i);
t_ast	*process_prompt(char *prompt, t_list *env);
t_ast	*create_ast(t_list *tok_list);
void 	ast_vw(t_ast *root);///////testing !!!!!
void	clear_token(t_token *token);
t_token	*get_next_token(char *input, int *i);
void	clear_ast(t_ast **ast);
bool	expand_ast_leafs(t_ast *ast, t_list *env);
void ast_vis(t_ast *ast, int level); ////testing
void	skip_quotes(char *s, int *i, char c);
char	**get_cmd_arr(char *s, t_list *env);
char	**expand_vars(char *s, t_list *env);


#endif