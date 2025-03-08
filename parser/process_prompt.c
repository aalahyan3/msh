/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:01:27 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/08 17:17:37 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	reverse_list(t_list **head)
{
	t_list	*prev;
	t_list	*curr;
	t_list	*next;

	if (!head || !*head)
		return ;
	prev = NULL;
	curr = *head;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	*head = prev;
}

t_ast	*process_prompt(char *prompt)
{
	t_list	*tok_list;
	t_ast	*ast;

	tok_list = tokenizer(prompt);
	if (!tok_list)
		return (NULL);
		reverse_list(&tok_list);
	ast = create_ast(tok_list);
	if (!ast)
		return (NULL);//free_tok_list(tok_list);
	ast_v(ast);
	return (ast);
}

