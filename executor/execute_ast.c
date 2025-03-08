/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:18:01 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/08 12:25:41 by aaitabde         ###   ########.fr       */
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

int is_builtin(char **args)
{
	if (ft_strncmp(args[0], "echo\0", 5) == 0)
		return (0);
	return (-1);
}

int	run_builting (char **args, char **env)
{
	if (args[0] && ft_strncmp(args[0], "echo", 5) == 0)
		return (ft_echo(args, env));
	return (-1);
}

int	execute_word(t_ast *ast, char **env)
{
	char **args = get_args(ast);
	if (is_builtin(args) == 0)
		return (run_builting(args, env));
	char *path = get_cmd_path(ast->token->value, env);
	if (path)
	{
		execute_simple_cmd(path, args, env);
		free(path);
		free_arr(args);
	}
	else
		ft_printf("minishell: %s: command not found\n", ast->token->value);
	return(1);
}

// void execute_pipe(t_ast *ast, char **env)
// {
// 	int		pipefd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	if (pipe(pipefd) == -1)
// 	{
// 		perror("pipe");
// 		return;
// 	}
// 	{
// 			dup2(pipefd[1], STDOUT_FILENO);
// 			close(pipefd[1]);
// 			execute_ast(ast->left, env);
// 			exit(0);
// 	}
// 	{
// 			dup2(pipefd[0], STDIN_FILENO);
// 			close(pipefd[0]);
// 			execute_ast(ast->right, env);
// 			exit(0);
// 	}
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, &status, 0);
// 	if (WTERMSIG( status))
// 		return WTERMSIG(statu) + 128;
// 	else
// 			return(WEXITSTATUS(status));
	
// }

void execute_ast(t_ast *ast, char **env)
{
	if(!ast)
		return ;
	// if (ast->token->key == PIPE)
	// 	execute_pipe(ast, env);
	if (ast->token->key == WORD)
		execute_word(ast, env);
	if (ast->left)
		execute_ast(ast->left, env);
	else if (ast->right && ast->right->token->key != WORD && ast->right->token->key != PIPE)
		execute_ast(ast->right, env);
}
