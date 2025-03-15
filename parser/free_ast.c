/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:16:20 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/14 22:19:25 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_ast(t_ast *ast)
{
	char	**args;
	t_reds	**reds;

	if (!ast)
		return ;
	free_ast(ast->left);
	free_ast(ast->right);
	if(ast->content)
		free(ast->content);
	if (ast->type == REDIRECTIONS)
	{
		if (!ast->data)
			return ;
		reds = (t_reds **)ast->data;
		free_red_structs(reds);
	}
	if (ast->type == COMMAND)
	{
		if (!ast->data)
			return ;
		args = (char **)ast->data;
		free_2d_array(args);
	}
	free(ast);
}