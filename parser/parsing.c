/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 08:57:28 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/23 19:58:44 by aalahyan         ###   ########.fr       */
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

t_ast	*parse(char *prompt)
{
	t_ast	*ast;
	if (!initial_checks(prompt))
		return (free(prompt), NULL);
	if (!linear_parsing(prompt))
		return (free(prompt), NULL);
	ast = process_prompt(prompt);
	if (!ast)
		return (NULL);
	ast_vis(ast, 0, "");
	if (!syntax_error(ast))
	{
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}