/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:18:01 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/08 08:55:08 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **get_args(t_ast *ast)
{
	char **args;

	args = NULL;
	if (ast->right && ast->right->token->value)
	{
		char *tmp = ft_strjoin(ast->token->value, " ");
		char *tmp1 = ft_strjoin(tmp, ast->right->token->value);
		args = ft_split(tmp1, ' ');
		free(tmp);
		free(tmp1);
	}
	else
	{
		args = malloc(2 * sizeof(char *));
		args[0] = ft_strdup(ast->token->value);
		args[1] = NULL;
	}
	return (args);
}

void execute_word(t_ast *ast, char **env)
{
	char *path = get_cmd_path(ast->token->value, env);

	if (path)
	{
		char **args = get_args(ast);
		execute_simple_cmd(path, args, env);
		free(path);
		free_arr(args);
	}
	else
		ft_printf("minishell: %s: command not found\n", ast->token->value);
}

void execute_ast(t_ast *ast, char **env)
{
	if (ast->left)
		execute_ast(ast->left, env);
	if (ast->token->key == WORD)
		execute_word(ast, env);
	if (ast->right && ast->right->token->key != WORD)
		execute_ast(ast->right, env);
}
