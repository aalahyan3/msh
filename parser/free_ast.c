/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 22:16:20 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/15 18:03:03 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_ast(t_ast *ast)
{
	char	**args;
	t_reds	**reds;
	t_ast	*left;
	t_ast	*right;

	if (!ast)
		return ;
	left = ast->left;
	right = ast->right;
	printf("freeing ast->content\n");
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
	free_ast(left);
	free_ast(right);
}