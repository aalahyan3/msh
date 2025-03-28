/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:06:01 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/28 19:45:34 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*get_root(t_list *tok_list)
{
	t_list	*root;
	t_list	*curr;
	bool	and_or_or;
	bool	first_pipe;
	bool	first_block;

	and_or_or = false;
	first_pipe = false;
	first_block = false;
	curr = tok_list;
	root = NULL;
	while (curr)
	{
		if (((t_tok *)curr->content)->type == OR || \
		((t_tok *)curr->content)->type == AND)
			1 && (root = curr, and_or_or = true);
		else if (((t_tok *)curr->content)->type == PIPE \
		&& !and_or_or && !first_pipe)
			1 && (root = curr, first_pipe = true);
		else if (!and_or_or && ((t_tok *)curr->content)->type == BLOCK \
		&& !first_block && !first_pipe)
			1 && (root = curr, first_block = true);
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
	if (curr == root)
		return (NULL);
	while (curr && curr != root)
	{
		prev = curr;
		curr = curr->next;
	}
	if (prev)
		prev->next = NULL;
	return (tok_list);
}

static void	free_tok(void *content)
{
	t_tok	*tok;

	tok = (t_tok *)content;
	free(tok->content);
	free(tok);
}

static t_ast	*ast_from_block(t_list *tok_list)
{
	char	*s;

	s = ft_strdup(((t_tok *)tok_list->content)->content);
	ft_lstclear(&tok_list, free_tok);
	return (expand_block(s));
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
		return (ast_from_block(tok_list));
	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	root = get_root(tok_list);
	ast->content = ft_strdup(((t_tok *)root->content)->content);
	ast->type = ((t_tok *)root->content)->type;
	ast->data = NULL;
	left = extract_left(tok_list, root);
	right = root->next;
	free(((t_tok *)root->content)->content);
	free(((t_tok *)root->content));
	free(root);
	ast->left = build_ast(left);
	ast->right = build_ast(right);
	return (ast);
}
