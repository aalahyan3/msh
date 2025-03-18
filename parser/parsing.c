/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 08:57:28 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/18 12:22:29 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	syntax_error(t_ast *ast)
{
	if (!ast)
		return (false);
	if (ast->type == PIPE || ast->type == AND || ast->type == OR)
	{
		if (!ast->left || !ast->right)
		{
			ft_printf("msh: syntax error near unexpected token '%s'\n", ast->content);
			return (false);
		}
		if (!syntax_error(ast->left) || !syntax_error(ast->right))
			return (false);
	}
	return (true);
}

t_ast	*parse(char *prompt, t_list *env_l)
{
	t_ast	*ast;

	ast = process_prompt(prompt, env_l);
	free(prompt);
	if (!ast)
		return (NULL);
	// ast_vis(ast, 0, "");
	if (!syntax_error(ast))
	{
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}