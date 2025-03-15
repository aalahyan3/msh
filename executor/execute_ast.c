/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:18:01 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/15 12:39:01 by aaitabde         ###   ########.fr       */
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

void	file_open_error(char *filename)
{
	write(2, "minishell: ", 11);
	write(2, filename, ft_strlen(filename));
	write(2, ": No such file or directory\n", 28);	
}

int handle_redirections(t_ast *ast, t_list *env)
{
	t_reds	**reds;
	int		red_count;
	int		infd;
	int		oufd;

	if (!ast || !ast->data)
		return (0);
	infd = STDIN_FILENO;
	oufd = STDOUT_FILENO;
	reds = (t_reds **)ast->data;
	red_count = 0;
	while (reds[red_count])
	{
		if (reds[red_count]->type == INPUT)
		{
			if (reds[red_count]->fd == -1)
				reds[red_count]->fd = open(reds[red_count]->file, O_RDONLY);
			if (reds[red_count]->fd < 0)
				return (perror("minishell : open"), 1);
			dup2(reds[red_count]->fd, STDIN_FILENO);
			close(reds[red_count]->fd);
		}
		else if (reds[red_count]->type == OUTPUT)
		{
			reds[red_count]->fd = open(reds[red_count]->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (reds[red_count]->fd < 0)
				return (perror("minishell : open"), 1);
			dup2(reds[red_count]->fd, STDOUT_FILENO);
			close(reds[red_count]->fd);
		}
		else if (reds[red_count]->type == APPEND)
		{
			reds[red_count]->fd = open(reds[red_count]->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (reds[red_count]->fd < 0)
				return (perror("minishell : open"), 1);
			dup2(reds[red_count]->fd, STDOUT_FILENO);
			close(reds[red_count]->fd);
		}
		red_count++;
	}
	return (0);
}

int	execute_block(t_ast *ast, t_list *env)
{
	pid_t	pid;
	int		status;

	if(!ast || !ast->left)
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		if (handle_redirections(ast->left, env) == 1)
			exit(1);
		exit(execute_ast(ast->right, env));
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute_ast(t_ast *ast, t_list *env)
{
	if (!ast)
		return (1);
	if (ast->type == BLOCK)
		return (execute_block(ast, env));
	if (ast->type == COMMAND)
		return (execute_word(ast, env));
	if (ast->type == AND || ast->type == OR)
		return (execute_logic(ast, env));
	if (ast->type == PIPE)
		return (execute_pipe(ast, env));
	return(1);
}
