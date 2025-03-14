/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:01:27 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/14 07:10:44 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*process_prompt(char *prompt, t_list *env)
{
	t_list	*tok_list;
	t_ast	*ast;

	if (!prompt)
		return (NULL);
	tok_list = tokenize(prompt);
	free(prompt);
	if (!tok_list)
		return (NULL);
	ast = build_ast(tok_list);
	// ast_vis(ast, 0, "");
	return (ast);
}