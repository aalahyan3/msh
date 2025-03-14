/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:18:01 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/14 09:15:20 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// int is_builtin(char **args)
// {
// 	if(!args || !*args)
// 		return(1);
// 	if (args && args[0] && ft_strncmp(args[0], "echo\0", 5) == 0)
// 		return (0);
// 	else if (args && args[0] && ft_strncmp(args[0], "pwd", 3) == 0)
// 		return (0);
// 	else if (args && args[0] && ft_strncmp(args[0], "cd\0", 3) == 0)
// 		return (0);
// 	return (-1);
// }

// int	run_builting (char **args, t_list *env)
// {
// 	if (args && args[0] && ft_strncmp(args[0], "echo", 5) == 0)
//  		return (ft_echo(args, env));
// 	if (args && args[0] && ft_strncmp(args[0], "pwd", 3) == 0)
// 		return (ft_pwd(env));
// 	if (args && args[0] && ft_strncmp(args[0], "cd", 2) == 0)
// 		return (ft_cd(args[1]));
// 	return (1);
// }

char	**make_env(t_list *ev)
{
	int		i;
	char	**env;
	char	*tmp;
	char	*tmp1;

	i = 0;
	env = (char **)malloc((ft_lstsize(ev) + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	while (ev)
	{
		tmp = ft_strjoin(((struct s_env*)(ev->content))->key, "=");
		if (!tmp)
			return (free_arr(env), NULL);
		tmp1 = ft_strjoin(tmp, ((struct s_env*)(ev->content))->value);
		if (!tmp1)
			return (free_arr(env), NULL);
		free(tmp);
		env[i] = tmp1;;
		ev = ev->next;
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	execute_word(t_ast *ast, t_list *ev)
{
	char	**args;
	char	*path;
	int		i;
	char	**env;

	if (!ast || !ast->data)
		return (1);
	env = make_env(ev);
	args = (char **)ast->data;
	// if (is_builtin(args) == 0)
	// 	return (run_builting(args, env));
	path = get_cmd_path(args[0], env, &i);
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
			write(2, args[0], ft_strlen(args[0]));
			write(2, ": command not found\n", 21);
		}
		return (free_arr(args), 127);
	}
	return (0);
}

int	execute_logic(t_ast *ast, t_list *env)
{
	int	status;

	status = execute_ast(ast->left, env);
	if ((status != 0 && ast->type == AND) || \
		(status == 0 && ast->type == OR))
		return (status);
	return(execute_ast(ast->right, env));
}


int	execute_ast(t_ast *ast, t_list *env)
{
	if (!ast)
		return (1);
	if (ast->type == BLOCK)
		return (execute_ast(ast->right, env));
	if (ast->type == COMMAND)
		return (execute_word(ast, env));
	if (ast->type == AND || ast->type == OR)
		return (execute_logic(ast, env));
	if (ast->type == PIPE)
		return (execute_pipe(ast, env));
	return(1);
}
 