/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 17:27:32 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/08 17:43:53 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include "../libft/libft.h"
enum e_token
{
	NONE,//0
	BLOCK,//1
	PIPE,//2
	WORD,//3
	WORD_SQ,//4
	WORD_DQ,//5
	REDIRECT_IN,//6
	REDIRECT_OUT,//7
	APPEND,//8
	HERE_DOC,//9
	HERE_DOC_END,//10
	AND,//11
	OR,//12
	WILD_CARD//13
};

typedef struct s_token
{
	char				*value;
	enum e_token		key;
}	t_token;

typedef struct s_ast
{
	t_token				*token;
	char				**args;   //ls -la token = ls , args = [ls, -la]
	struct s_ast		*left;
	struct s_ast		*right;
}	t_ast;

int		get_word(t_token **token, char *input, int *i);
t_list	*tokenizer(char *input);
char	*get_block(char *input, int *i);
t_ast	*process_prompt(char *prompt);
t_ast	*create_ast(t_list *tok_list);
void 	ast_v(t_ast *root);///////testing !!!!!


#endif