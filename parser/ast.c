/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:55:32 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/09 22:59:05 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*resolve_block(t_token *token)
{
	t_list	*tok_list_block;
	char	*temp;
	t_ast	*ast;

	temp = ft_strtrim(token->value, "()");
	if (!temp)
		return (NULL);
	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (free(temp), NULL);
	free(token->value);
	token->value = temp;
	tok_list_block = tokenizer(token->value);
	if (!tok_list_block)
		return (NULL);
	ast = create_ast(tok_list_block);
	return (ast);
}

int get_precedence(enum e_token key)
{
	if (key == AND)
		return -1;
	if (key == OR)
		return -2;
	if (key == PIPE)
		return 3;
	if (key == REDIRECT_IN || key == REDIRECT_OUT || key == APPEND || key == HERE_DOC)
		return 4;
	return 5;
}

t_list	*get_root_node(t_list *tok_list)
{
	t_list	*curr;
	t_list	*root;
	int		lowest;
	int		precedence;
	int		order;

	curr = tok_list;
	root = NULL;
	lowest = 999;
	order  = 0;
	while (curr)
	{
		precedence = get_precedence(((t_token *)curr->content)->key);
		if (((t_token *)curr->content)->key == AND || ((t_token *)curr->content)->key == OR)
		{
			root = curr;
			order = 1;
		}
		else if (precedence > 0 && precedence < lowest && !order)
		{
			root = curr;
			lowest = precedence;
		}
		curr = curr->next;
	}
	return (root);
}

t_list	*extract_left(t_list **tok_list, t_list *root)
{
	t_list	*curr;
	t_list	*left;

	curr = *tok_list;
	left = *tok_list;
	if (curr == root)
	{
		*tok_list = (*tok_list)->next;
		return (NULL);
	}
	while (curr && curr->next != root)
		curr = curr->next;
	if (curr)
	{
		curr->next = NULL;
		*tok_list = root->next;
		root->next = NULL;
		return (left);
	}
	return (NULL);
}
t_ast	*one_token_ast(t_list *node)
{
	t_ast	*ast;

	if (((t_token *)node->content)->key == BLOCK)
	{
		ast = resolve_block(node->content);
		return (free(node), ast);
	}
	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (free(node), NULL);
	ast->token = node->content;
	ast->left = NULL;
	ast->right = NULL;
	return (free(node), ast);
}

t_ast *create_ast(t_list *tok_list)
{
	t_list *root;
	t_list *left;
	t_list *right;
	t_ast *ast;

	if (!tok_list)
		return NULL;
	if (ft_lstsize(tok_list) == 1)
		return (one_token_ast(tok_list));
	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	root = get_root_node(tok_list);
	if (!root)
		return (free(ast), NULL);
	left = extract_left(&tok_list, root);
	right = tok_list;
	ast->token = root->content;
	ast->left = create_ast(left);
	ast->right = create_ast(right);
	free(root);
	return (ast);
}
