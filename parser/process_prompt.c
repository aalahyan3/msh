/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:01:27 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/09 20:54:53 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_token(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}

t_ast	*process_prompt(char *prompt)
{
	t_list	*tok_list;
	t_ast	*ast;

	tok_list = tokenizer(prompt);
	if (!tok_list)
		return (NULL);
	for(t_list *curr = tok_list; curr; curr = curr->next)
	{
		t_token *token = curr->content;
		printf("key: %d, value: %s\n", token->key, token->value);
	}
	if (!tok_list)
		return (NULL);
	ast = create_ast(tok_list);
	if (!ast)
	{
		ft_lstclear(&tok_list, clear_token);
		return (NULL);
	}
	ast_vw(ast);
	return (ast);
}

