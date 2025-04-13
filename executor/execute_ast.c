/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:18:01 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/13 20:06:40 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute_logic(t_msh *msh, t_ast *ast)
{
	int	status;

	status = execute_ast(msh, ast->left);
	if ((status != 0 && ast->type == AND) || \
		(status == 0 && ast->type == OR))
	{
		close_hds_rec(ast->right);
		return (status);
	}
	return (execute_ast(msh, ast->right));
}

static void	reset_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static int	execute_block_part1(t_msh *msh, t_ast *ast, \
int *saved_stdin, int *saved_stdout)
{
	int	status;

	if (!ast || !ast->left)
		return (1);
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(ast->left, msh))
	{
		close(*saved_stdin);
		close(*saved_stdout);
		return (1);
	}
	if (ast && ast->right && ast->right->type == BLOCK)
	{
		status = execute_ast(msh, ast->right);
		reset_fd(*saved_stdin, *saved_stdout);
		return (status);
	}
	return (-1);
}

int	execute_block(t_msh *msh, t_ast *ast)
{
	int		status;
	char	**expanded_args;
	char	**args;
	int		saved_stdin;
	int		saved_stdout;

	status = execute_block_part1(msh, ast, &saved_stdin, &saved_stdout);
	if (status != -1)
		return (status);
	args = (char **)ast->right->data;
	expanded_args = expand(args, msh);
	if (expanded_args && expanded_args[0] && !expanded_args[0][0])
		return (ft_printf_error(expanded_args[0], ": ", "command not found", \
		"\n"), free_2d_array(expanded_args), \
		reset_fd(saved_stdin, saved_stdout), \
		close(saved_stdin), close(saved_stdout), 127);
	if (expanded_args && is_builtin(expanded_args) == 0)
	{
		status = run_builting(msh, args, expanded_args);
		return (free_2d_array(expanded_args), reset_fd(saved_stdin, \
		saved_stdout), status);
	}
	free_2d_array(expanded_args);
	status = execute_ast(msh, ast->right);
	return (reset_fd(saved_stdin, saved_stdout), status);
}

int	execute_ast(t_msh *msh, t_ast *node)
{
	signal(SIGQUIT, donothing);
	signal(SIGINT, donothing);
	if (!node)
		return (1);
	if (node->type == BLOCK)
		return (execute_block(msh, node));
	if (node->type == COMMAND)
		return (execute_word(msh, node));
	if (node->type == AND || node->type == OR)
		return (execute_logic(msh, node));
	if (node->type == PIPE)
		return (execute_pipe(msh, node));
	return (1);
}
