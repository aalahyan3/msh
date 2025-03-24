/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:32:16 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/23 19:58:55 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_tok(void *content)
{
	t_tok	*tok;

	tok = (t_tok *)content;
	free(tok->content);
	free(tok);
}

static void	free_tok_not_content(void *content)
{
	t_tok	*tok;

	tok = (t_tok *)content;
	free(tok);
}

t_ast	*process_prompt(char *prompt)
{
	t_list	*tok_list;
	t_ast	*ast;

	if (!prompt || !*prompt)
		return (NULL);
	tok_list = tokenize(prompt);
	free(prompt);
	if (!tok_list)
		return (NULL);
	ast = build_ast(tok_list);
	if (!ast)
	{
		return (NULL);
	}
	return (ast);
}
