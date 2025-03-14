/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:06:01 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/14 07:39:14 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list *get_root(t_list *tok_list)
{
	t_list *root;
	t_list	*curr;
	bool	and_or_or;

	curr = tok_list;
	root = NULL;
	and_or_or = false;
	while (curr)
	{
		if (((t_tok *)curr->content)->type == OR || ((t_tok *)curr->content)->type == AND)
		{
			root = curr;
			and_or_or = true;
		}
		else if (((t_tok *)curr->content)->type == PIPE && !and_or_or)
		{
			root = curr;
		}
		else if (!and_or_or && ((t_tok *)curr->content)->type == BLOCK)
		{
			root = curr;
		}
		curr = curr->next;
	}
	return (root);
}

t_list	*extract_left(t_list *tok_list, t_list *root)
{
	t_list	*curr;
	t_list	*prev;

	curr = tok_list;
	prev = NULL;
	while (curr && curr != root)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev)
		prev->next = NULL;
	return (tok_list);
}




t_ast	*build_ast(t_list *tok_list)
{
	t_ast	*ast;
	t_list	*left;
	t_list	*right;
	t_list	*root;

	if (!tok_list)
		return (NULL);
	if (ft_lstsize(tok_list) == 1)
	{
		return (expand_block(((t_tok *)(tok_list->content))->content));
	}
	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	root = get_root(tok_list);
	if (!root)
		return (NULL);
	if (((t_tok *)root->content)->type == BLOCK)
	{
		free(ast);
		return (expand_block(((t_tok *)(root->content))->content));
	}
	ast->content = ((t_tok *)root->content)->content;
	ast->type = ((t_tok *)root->content)->type;
	ast->data = NULL;
	left = extract_left(tok_list, root);
	right = root->next;
	ast->left = build_ast(left);
	ast->right = build_ast(right);
	return (ast);
}
