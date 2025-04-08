/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:32:16 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/08 15:38:33 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	return (ast);
}
