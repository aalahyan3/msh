/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_v.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:28:56 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/10 18:03:32 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>
void print_red_files(t_ast *ast)
{
	t_red **red = (t_red **)ast->data;
	printf("%s\n", red[0]->name);
	for (int i = 0; red[i] ; i++)
		printf("file %s , key = %d\n", red[i]->name, red[i]->type);
}

void ast_vis(t_ast *ast, int level)
{
	if (!ast)
		return ;
	t_token *tok = (t_token *)ast->token;
	if (tok->key == COMMAND)
	{
		printf("command data:\n");
		print_red_files(ast->left);
	}
	else
	{
		printf("root = %d\n", ((t_token *)ast->token)->key);
		ast_vis(ast->left, level++);
		int	l = level--;
		ast_vis(ast->right, level--);
	}
}