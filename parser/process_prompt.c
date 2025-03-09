/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:01:27 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/09 12:33:35 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_ast	*process_prompt(char *prompt)
{
	t_list	*tok_list;
	t_ast	*ast;

	tok_list = tokenizer(prompt);
	if (!tok_list)
		return (NULL);
	ast = create_ast(tok_list);
	if (!ast)
		return (NULL);//free_tok_list(tok_list);
	// debug_ast_centered(ast);
	return (ast);
}
