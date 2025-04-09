/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:18:01 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/09 15:57:45 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int is_builtin(char **args)
{
	if(!args || !*args)
		return(1);
	if (args && args[0] && ft_strncmp(args[0], "echo\0", 5) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "pwd\0", 4) == 0)
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
 		return (ft_echo(args, msh));
	else if (args && args[0] && ft_strncmp(args[0], "pwd", 3) == 0)
		return (ft_pwd(msh->env));
	else if (args && args[0] && ft_strncmp(args[0], "cd", 2) == 0)
		return (ft_cd(args[1], msh));
	else if (args && args[0] && ft_strncmp(args[0], "env", 3) == 0)
		return (ft_env(msh->env));
	else if (args && args[0] && ft_strncmp(args[0], "unset", 5) == 0)
		return (ft_unset(msh->env, args));
	else if (args && args[0] && ft_strncmp(args[0], "export", 6) == 0)
		return (ft_export(args, msh));
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
	char	*path_var;
	int		i;
	char	**env;

	if (!ast || !ast->data)
		return (1);
	env = make_env(msh->env);
	args = expand((char **)ast->data, msh);
	i = 0;
	if(!args)
		return (1);
	if (args[0] && args[0][0] == '\0')
		return (0);
	if (args[0] && !args[0][0])
	{
		write(2, "msh: ", 6);
		write(2, ":command not found\n", 19);
		return (1);
	}
	path_var = get_from_env("PATH", msh->env);
	if (!path_var)
	{
		if (access(args[0], F_OK) == 0)
		{
			if (access(args[0], X_OK) == 0)
				return (execute_simple_cmd(args[0], args, env));
			ft_printf_error(args[0], ": ", "Permission denied", "\n");
			free_2d_array(env);
			return(126);
		}
		ft_printf_error(args[0], ": ", strerror(errno), "\n");
		free_arr(args);
		free_2d_array(env);
		return (127);
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
		free_2d_array(env);
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

 int	expand_heredoc(int fd, t_msh *msh)
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
		line = expand_here_doc(tmp, msh);
		write(new_fd, line, ft_strlen(line));
		free(tmp);
		free(line);
	}
	close(fd);
	return(new_fd_read);
 }

// int handle_redirections(t_ast *ast, t_msh *msh, int *saved_stdin, int *saved_stdout)
// {
// 	t_reds	**reds;
// 	int		red_count;
// 	char	**args;

// 	if (!ast || !ast->data)
// 		return (0);
// 	*saved_stdin = dup(STDIN_FILENO);
// 	*saved_stdout = dup(STDOUT_FILENO);
// 	reds = (t_reds **)ast->data;
// 	red_count = 0;
// 	while (reds[red_count])
// 	{
// 		if (reds[red_count]->is_hd)
// 		{
// 			dup2(reds[red_count]->fd, STDIN_FILENO);
// 			// printf("%s\n", get_next_line(reds[red_count]->fd));
// 			red_count++;
// 			continue ;
// 		}
// 		args = expand_filename(reds[red_count]->file, msh);
// 		if (!args || (args[0] && args[1] ))
// 		{
// 			ft_putstr_fd("msh: ", 2);
// 			ft_putstr_fd(reds[red_count]->file, 2);
// 			ft_putstr_fd(": ambiguous redirect\n", 2);
// 			free_arr(args);
// 			return (1);
// 		}
// 		reds[red_count]->file = ft_strdup(args[0]);
// 		free_arr(args);
// 		if (reds[red_count]->type == INPUT)
// 		{
// 			if (reds[red_count]->fd == -1)
// 				reds[red_count]->fd = open(reds[red_count]->file, O_RDONLY);
// 			else
//  				reds[red_count]->fd = expand_heredoc(reds[red_count]->fd, msh);
// 			if (reds[red_count]->fd < 0)
// 			{
// 				write(2, "msh: ", 6);
// 				perror(reds[red_count]->file);
// 				return (1);
// 			}
// 			dup2(reds[red_count]->fd, STDIN_FILENO);
// 			close(reds[red_count]->fd);
// 		}
// 		else if (reds[red_count]->type == OUTPUT)
// 		{
// 			reds[red_count]->fd = open(reds[red_count]->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (reds[red_count]->fd < 0)
// 			{
// 				write(2, "msh: ", 6);
// 				perror(reds[red_count]->file);
// 				return (1);
// 			}
// 			dup2(reds[red_count]->fd, STDOUT_FILENO);
// 			close(reds[red_count]->fd);
// 		}
// 		else if (reds[red_count]->type == APPEND)
// 		{
// 			reds[red_count]->fd = open(reds[red_count]->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 			if (reds[red_count]->fd < 0)
// 			{
// 				write(2, "msh: ", 6);
// 				perror(reds[red_count]->file);
// 				return (1);
// 			}
// 			dup2(reds[red_count]->fd, STDOUT_FILENO);
// 			close(reds[red_count]->fd);
// 		}
// 		red_count++;
// 	}
// 	return (0);
// }

void reset_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	was_hd(t_reds *red, t_msh *msh)
{
	int	expand;
	char	*line;
	char	*expanded;
	int		fd;
	char	*name;

	expand = 1;
	if (ft_strchr(red->file, '\'') || ft_strchr(red->file, '"'))
		expand = 0;
	if (!expand)
		return (red->fd);
	name = gen_name();
	fd = open(name, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (-1);
	line = get_next_line(red->fd);
	while (line)
	{
		expanded = expand_here_doc(line, msh);
		if (!expanded)
		{
			free(line);
			return (-1);
		}
		if (*expanded == '\n')
		{
			free(expanded);
			free(line);
			line = get_next_line(red->fd);
			continue ;
		}
		write(fd, expanded, ft_strlen(expanded));
		free(expanded);
		free(line);
		line = get_next_line(red->fd);
	}
	close(fd);
	fd = open(name, O_RDONLY);
	close(red->fd);
	return (fd);
}

void	ft_close(int *fd)
{
	if (*fd > 0)
	{
		close(*fd);
		*fd = -1;
	}
}

int	handle_redirections(t_ast *ast, t_msh *msh)
{
	int	in_fd;
	int	out_fd;
	int	i;
	t_reds	**reds;

	if (!ast->data)
		return (0);
	reds = (t_reds **)(ast->data);
	i = 0;
	in_fd = -1;
	out_fd = -1;
	while (reds[i])
	{
		if (reds[i]->type == HEREDOC)
		{
			ft_close(&in_fd);
			in_fd = was_hd(reds[i], msh);
			if (in_fd < 0)
			{
				return (1);
			}
		}
		else if (reds[i]->type == INPUT)
		{
			ft_close(&in_fd);
			in_fd = open(reds[i]->file, O_RDONLY);
			if (in_fd < 0)
			{
				ft_printf_error(reds[i]->file, ": ", strerror(errno), "\n");
				return (1);
			}
		}
		else if (reds[i]->type == OUTPUT)
		{
			ft_close(&out_fd);
			out_fd = open(reds[i]->file, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if (out_fd < 0)
			{
				ft_printf_error(reds[i]->file, ": ", strerror(errno), "\n");
				return (1);
			}
		}
		else if (reds[i]->type == APPEND)
		{
			ft_close(&out_fd);
			out_fd = open(reds[i]->file, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (out_fd < 0)
				return (1);
		}
		i++;
	}
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	ft_close(&in_fd);
	ft_close(&out_fd);
	return (0);
}

int	execute_block(t_msh *msh, t_ast *ast)
{
	int		status;
	char	**args;
	int		saved_stdin;
	int		saved_stdout;

	if (!ast || !ast->left)
		return (1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(ast->left, msh) == 1)
		return (1);
	args = expand ((char **)ast->right->data, msh);
	if (args)
	{
		if (!is_builtin(args))
		{
			status = run_builting(msh, args);
			free_2d_array(args);
			reset_fd(saved_stdin, saved_stdout);
			return (status);
		}
	}
	status = execute_ast(msh, ast->right);
	reset_fd(saved_stdin, saved_stdout);
	return (status);
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
	return(1);
}
