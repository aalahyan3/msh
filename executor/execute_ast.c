/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:18:01 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/26 04:29:15 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int is_builtin(char **args)
{
	if(!args || !*args)
		return(1);
	if (args && args[0] && ft_strncmp(args[0], "echo\0", 5) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "pwd", 3) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "cd\0", 3) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "export\0", 7) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "env\0", 4) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "unset\0", 6) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "exit\0", 5) == 0)
		return (0);
	return (-1);
}

int	run_builting (t_msh *msh, char **args)
{
	if (args && args[0] && ft_strncmp(args[0], "echo", 5) == 0)
 		return (ft_echo(args, msh->env));
	else if (args && args[0] && ft_strncmp(args[0], "pwd", 3) == 0)
		return (ft_pwd(msh->env));
	else if (args && args[0] && ft_strncmp(args[0], "cd", 2) == 0)
		return (ft_cd(args[1], msh));
	else if (args && args[0] && ft_strncmp(args[0], "env", 3) == 0)
		return (ft_env(msh->env));
	else if (args && args[0] && ft_strncmp(args[0], "unset", 5) == 0)
		return (ft_unset(msh->env, args));
	else if (args && args[0] && ft_strncmp(args[0], "export", 6) == 0)
		return (ft_export(args, msh->env));
	else if (args && args[0] && ft_strncmp(args[0], "exit", 4) == 0)
		ft_exit(msh, args);
	return (1);
}

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

void do_nothing(int sig);

int	execute_word(t_msh *msh, t_ast *ast)
{
	char	**args;
	char	*path;
	int		i;
	char	**env;

	if (!ast || !ast->data)
		return (1);
	env = make_env(msh->env);
	args = expand((char **)ast->data, msh->env);
	i = 0;
	if(!args)
		return (1);
	if (args[0] && !args[0][0])
	{
		write(2, "msh: ", 6);
		write(2, ":command not found\n", 19);
		return (1);
	}
	path = get_cmd_path(args[0], env, &i);
	if (path)
		return (execute_simple_cmd(path, args, env));
	else
	{
		if (i)
		{
			write(2, "msh: ", 6);
			write(2, args[0], ft_strlen(args[0]));
			write(2, ": command not found\n", 21);
		}
		return (free_arr(args), 127);
	}
	return (0);
}

int	execute_logic(t_msh *msh, t_ast *ast)
{
	int	status;

	status = execute_ast(msh, ast->left);
	if ((status != 0 && ast->type == AND) || \
		(status == 0 && ast->type == OR))
		return (status);
	return(execute_ast(msh, ast->right));
}

void	file_open_error(char *filename)
{
	write(2, "msh: ", 6);
	write(2, filename, ft_strlen(filename));
	write(2, ": No such file or directory\n", 28);	
}

 int	expand_heredoc(int fd, t_list *env)
 {
	char *line;
	char *filename = gen_name();
	
	int new_fd = open(filename, O_RDWR | O_CREAT , 0644);
	int new_fd_read = open(filename, O_RDONLY | O_CREAT , 0640);
	unlink(filename);
	free(filename);
	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		char *tmp = line;
		line = expand_here_doc(tmp, env);
		write(new_fd, line, ft_strlen(line));
		free(tmp);
		free(line);
	}
	close(fd);
	return(new_fd_read);
 }

int handle_redirections(t_ast *ast, t_list *env, int *saved_stdin, int *saved_stdout)
{
	t_reds	**reds;
	int		red_count;
	char	**args;

	if (!ast || !ast->data)
		return (0);
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	reds = (t_reds **)ast->data;
	red_count = 0;
	while (reds[red_count])
	{
		args = expand_filename(reds[red_count]->file, env);
		if (!args || (args[0] && args[1] ))
		{
			ft_putstr_fd("msh: ", 2);
			ft_putstr_fd(reds[red_count]->file, 2);
			ft_putstr_fd(": ambiguous redirect\n", 2);
			free_arr(args);
			return (1);
		}
		reds[red_count]->file = ft_strdup(args[0]);
		free_arr(args);
		if (reds[red_count]->type == INPUT)
		{
			if (reds[red_count]->fd == -1)
				reds[red_count]->fd = open(reds[red_count]->file, O_RDONLY);
			else
 				reds[red_count]->fd = expand_heredoc(reds[red_count]->fd, env);
			if (reds[red_count]->fd < 0)
			{
				write(2, "msh: ", 6);
				perror(reds[red_count]->file);
				return (1);
			}
			dup2(reds[red_count]->fd, STDIN_FILENO);
			close(reds[red_count]->fd);
		}
		else if (reds[red_count]->type == OUTPUT)
		{
			reds[red_count]->fd = open(reds[red_count]->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (reds[red_count]->fd < 0)
			{
				write(2, "msh: ", 6);
				perror(reds[red_count]->file);
				return (1);
			}
			dup2(reds[red_count]->fd, STDOUT_FILENO);
			close(reds[red_count]->fd);
		}
		else if (reds[red_count]->type == APPEND)
		{
			reds[red_count]->fd = open(reds[red_count]->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (reds[red_count]->fd < 0)
			{
				write(2, "msh: ", 6);
				perror(reds[red_count]->file);
				return (1);
			}
			dup2(reds[red_count]->fd, STDOUT_FILENO);
			close(reds[red_count]->fd);
		}
		red_count++;
	}
	return (0);
}

void reset_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	execute_block(t_msh *msh, t_ast *ast)
{
	int		status;
	char	**args;
	int		is_builtin_command;
	int		saved_stdin;
	int		saved_stdout;

	if (!ast || !ast->left)
		return (1);
	args = (char **)ast->right->data;
	if (handle_redirections(ast->left, msh->env, &saved_stdin, &saved_stdout) == 1)
		return (1);
	is_builtin_command = is_builtin(args);
	if (is_builtin_command == 0)
		status = run_builting(msh, args);
	else
		status = execute_ast(msh, ast->right);
	reset_fd(saved_stdin, saved_stdout);
	return (status);
}

int	execute_ast(t_msh *msh, t_ast *node)
{
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
	return(1);
}
