/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:18:01 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/10 23:51:26 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_builtin(char **args)
{
	if (ft_strncmp(args[0], "echo\0", 5) == 0)
		return (0);
	else if (args[0] && ft_strncmp(args[0], "pwd", 3) == 0)
		return (0);
	else if (args[0] && ft_strncmp(args[0], "cd", 2) == 0)
		return (0);
	return (-1);
}

int	run_builting (char **args, char **env)
{
	if (args[0] && ft_strncmp(args[0], "echo", 5) == 0)
 		return (ft_echo(args, env));
	if (args[0] && ft_strncmp(args[0], "pwd", 3) == 0)
		return (ft_pwd(env));
	if (args[0] && ft_strncmp(args[0], "cd", 2) == 0)
		return (ft_cd(args[1]));
	return (1);
}

int	execute_word(t_ast *ast, char **env)
{
	char	**args;
	char	*path;
	int		i;

	args = (char **)ast->data;
	printf("args = %s\n", args[0]);
	printf("args[0] = %s\n", args[0]);
	printf("args[1] = %s\n", args[1]);
	if (is_builtin(args) == 0)
		return (run_builting(args, env));
	path = get_cmd_path(ast->token->value, env, &i);
	if (path)
	{
		execute_simple_cmd(path, args, env);
		free(path);
		free_arr(args);
	}
	else
	{
		if (i)
		{
			write(2, "minishell: ", 11);
			write(2, ast->token->value, ft_strlen(ast->token->value));
			write(2, ": command not found\n", 21);
		}
		return (free_arr(args), 127);
	}
	return (0);
}

int	execute_logic(t_ast *ast, char **env)
{
	int	status;

	status = execute_ast(ast->left, env);
	if ((status != 0 && ast->token->key == AND) || \
		(status == 0 && ast->token->key == OR))
		return (status);
	return(execute_ast(ast->right, env));
}

int	execute_ast(t_ast *ast, char **env)
{
	if (!ast)
		return (1);
	if (ast->token->key == PIPE)
		return (execute_pipe(ast, env));
	if (ast->token->key == AND || ast->token->key == OR)
		return (execute_logic(ast, env));
	if (ast->token->key == COMMAND)
		return (execute_word(ast->right, env));
	return (1);
}
