/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:18:01 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/11 20:02:19 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int is_builtin(char **args)
{
	if(!args || !*args)
		return(1);
	if (args && args[0] && ft_strncmp(args[0], "echo", 5) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "pwd", 4) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "cd", 3) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "export", 7) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "env", 4) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "unset", 6) == 0)
		return (0);
	else if (args && args[0] && ft_strncmp(args[0], "exit", 5) == 0)
		return (0);
	return (-1);
}

int	run_builting (t_msh *msh, char **args, char **expanded_args)
{
	if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], "echo", 5) == 0)
 		return (ft_echo(expanded_args, msh));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], "pwd", 4) == 0)
		return (ft_pwd(msh->env));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], "cd", 3) == 0)
		return (ft_cd(expanded_args[1], msh));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], "env", 3) == 0)
		return (ft_env(msh->env));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], "unset", 6) == 0)
		return (ft_unset(msh->env, expanded_args));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], "export", 7) == 0)
		return (ft_export(args, msh));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], "exit", 5) == 0)
		ft_exit(msh, expanded_args);
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
	args = (char **)ast->data;
	if(!args)
		return (1);
	if (args[0] && args[0][0] == '\0')
		return (0);
	args = expand((char **)ast->data, msh);
	if (!args[0])
	{
		free_2d_array(args);
		free_2d_array(env);
		return(0);
	}
	i = 0;
	if (args[0] && !args[0][0])
	{
		write(2, "msh: ", 6);
		write(2, ":command not found\n", 19);
		free_2d_array(args);
		free_2d_array(env);
		return (1);
	}
	path_var = get_from_env("PATH", msh->env);
	if (!path_var)
	{
		if (access(args[0], F_OK) == 0)
		{
			if (access(args[0], X_OK) == 0)
				return (execute_simple_cmd(ft_strdup(args[0]), args, env));
			ft_printf_error(args[0], ": ", "Permission denied", "\n");
			free_2d_array(env);
			free_2d_array(args);
			return (126);
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
	return (new_fd_read);
}

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
		return (free(name), -1);
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
	close(red->fd);
	close(fd);
	fd = open(name, O_RDONLY);
	unlink(name);
	free(name);
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

void	close_hds(t_reds **reds)
{
	int i = 0;
	while (reds[i])
	{
		if (reds[i]->type == HEREDOC)
			close(reds[i]->fd);
		i++;
	}
}
int	handle_redirections(t_ast *ast, t_msh *msh)
{
	int	in_fd;
	int	out_fd;
	int	i;
	t_reds	**reds;
	char	**filename;

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
				ft_close(&in_fd);
				close_hds(reds);
				return (1);
			}
		}
		else if (reds[i]->type == INPUT)
		{
			ft_close(&in_fd);
			filename = expand_filename(reds[i]->file, msh);
			if (!filename || !*filename[0] || filename[1])
			{
				if (filename && !*filename[0])
					ft_printf_error(filename[0], ": ", "No such file or directory\n", NULL);
				else
					ft_printf_error(reds[i]->file, ": ", " ambiguous redirect\n", NULL);
				close_hds(reds);
				if (filename)
					free_2d_array(filename);
				ft_close(&out_fd);
				return (1);
			}
			in_fd = open(filename[0], O_RDONLY);
			free_2d_array(filename);
			if (in_fd < 0)
			{
				ft_printf_error(reds[i]->file, ": ", strerror(errno), "\n");
				close_hds(reds);
				ft_close(&out_fd);
				return (1);
			}
		}
		else if (reds[i]->type == OUTPUT)
		{
			ft_close(&out_fd);
			filename = expand_filename(reds[i]->file, msh);
			if (!filename || !*filename[0] || filename[1])
			{
				close_hds(reds);
				if (filename && !*filename[0])
					ft_printf_error(filename[0], ": ", "No such file or directory\n", NULL);
				else
					ft_printf_error(reds[i]->file, ": ", " ambiguous redirect\n", NULL);
				if (filename)
					free_2d_array(filename);
				ft_close(&in_fd);
				return (1);
			}
			out_fd = open(filename[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
			free_2d_array(filename);
			if (out_fd < 0)
			{
				ft_printf_error(reds[i]->file, ": ", strerror(errno), "\n");
				close_hds(reds);
				ft_close(&in_fd);
				return (1);
			}
		}
		else if (reds[i]->type == APPEND)
		{
			ft_close(&out_fd);
			filename = expand_filename(reds[i]->file, msh);
			if (!filename || !*filename[0] || filename[1])
			{
				ft_close(&in_fd);
				close_hds(reds);
				if (filename && !*filename[0])
					ft_printf_error(filename[0], ": ", "No such file or directory\n", NULL);
				else
					ft_printf_error(reds[i]->file, ": ", " ambiguous redirect\n", NULL);
				if (filename)
					free_2d_array(filename);
				return (1);
			}
			out_fd = open(filename[0], O_CREAT | O_RDWR | O_APPEND, 0644);
			free_2d_array(filename);
			if (out_fd < 0)
			{
				ft_printf_error(reds[i]->file, ": ", strerror(errno), "\n");
				close_hds(reds);
				ft_close(&in_fd);
				return (1);
			}
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
	char	**expanded_args;
	char	**args;
	int		saved_stdin;
	int		saved_stdout;

	if (!ast || !ast->left)
		return (1);
	if (handle_redirections(ast->left, msh))
	{
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	if (ast && ast->right && ast->right->type == BLOCK)
		return(execute_ast(msh, ast->right));
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	args = (char **)ast->right->data;
	if (args && is_builtin(args) == 0)
	{
		status = run_builting(msh, args, expanded_args);
		free_2d_array(expanded_args);
		reset_fd(saved_stdin, saved_stdout);
		return (status);
	}
	expanded_args = expand(args, msh);
	if (expanded_args && expanded_args[0] && !expanded_args[0][0])
	{
		free_2d_array(expanded_args);
		close(saved_stdin);
		close(saved_stdout);
		return (127);
	}
	free_2d_array(expanded_args);
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
