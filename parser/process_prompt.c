/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:32:16 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/14 09:21:33 by aalahyan         ###   ########.fr       */
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
	if (!tok_list)
		return (NULL);
	ast = build_ast(tok_list);
	return (ast);
}