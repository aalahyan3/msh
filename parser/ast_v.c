/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_v.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:28:56 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/13 00:28:34 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

char	*get_action(enum e_red_type t)
{
	if (t == OUTPUT)
		return "write";
	if (t == INPUT)
		return "read";
	if (t == APPEND)
		return "append";
	if (t == HERE_DOC)
		return "here_doc";
}
void print_red_files(t_ast *ast)
{
	if (!ast)
		return ;
	printf("redirections:\n");
	t_red **red = (t_red **)ast->data;
	for (int i = 0; red[i] ; i++)
		printf("{%d} action: %s file :%s\n", i, get_action(red[i]->type), red[0]->name);
}


void print_cmd_data(t_ast *ast)
{
	if (!ast)
		return ;
	char	**arr = (char **)(ast->data);
	if (!arr)
		return ;
			printf("command and args:\n");
	for (int i = 0; arr[i]; i++)
		printf("argv[%d] = %s\n", i,arr[i]);
}
void ast_vis(t_ast *ast, int level)
{
	if (!ast)
		return ;
	t_token *tok = (t_token *)ast->token;
	if (tok->key == COMMAND)
	{
		print_red_files(ast->left);
		print_cmd_data(ast->right);
	}
	else
	{
		printf("root = %d\n", ((t_token *)ast->token)->key);
		ast_vis(ast->left, level++);
		int	l = level--;
	}
}