/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:01:27 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/08 01:30:45 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	process_prompt(char *prompt)
{
	t_list	*tok_list;
	t_ast	*ast;

	tok_list = tokenizer(prompt);
	if (!tok_list)
		return ;
	ft_printf("\n");
	ast = create_ast(tok_list);
	debug_ast_centered(ast);
}
