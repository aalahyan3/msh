/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:32:16 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/22 16:00:57 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_tok(void *content)
{
	t_tok	*tok;

	tok = (t_tok *)content;
	printf("freeing tok: %s[%p]", tok->content, tok->content);
	free(tok->content);
	free(tok);
}

static void	free_tok_not_content(void *content)
{
	t_tok	*tok;

	tok = (t_tok *)content;
	free(tok);
}

t_ast	*process_prompt(char *prompt, t_list *env)
{
	t_list	*tok_list;
	t_ast	*ast;

	if (!prompt || !*prompt)
		return (NULL);
	tok_list = tokenize(prompt);
	if (!tok_list)
		return (NULL);
	ast = build_ast(tok_list);
	if (!ast)
	{
		return (NULL);
	}
	return (ast);
}
