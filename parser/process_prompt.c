/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:01:27 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/12 17:16:46 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_ast(t_ast **ast)
{
	t_ast	*left;
	t_ast	*right;

	left = (*ast)->left;
	right = (*ast)->right;
	clear_token((*ast)->token);
	free(*ast);
	*ast = NULL;
	if (left)
		clear_ast(&left);
	if (right)
		clear_ast(&right);
}

void	clear_token(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}

t_ast	*process_prompt(char *prompt, t_list *env)
{
	t_list	*tok_list;
	t_ast	*ast;

	tok_list = tokenizer(prompt);
	if (!tok_list)
		return (NULL);
	ast = create_ast(tok_list);
	if (!ast)
	{
		ft_lstclear(&tok_list, NULL);
		return (NULL);
	}
	if (!expand_ast_leafs(ast, env))
	{
		clear_ast(&ast);
		return (NULL);
	}
	// ast_vw(ast);
	return (ast);
}

