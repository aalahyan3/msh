/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:18:01 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/13 17:43:26 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	is_builtin(char **args)
{
	if (!args || !*args)
		return (1);
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

int	run_builting(t_msh *msh, char **args, char **expanded_args)
{
	if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], "echo", 5) == 0)
 		return (ft_echo(expanded_args, msh));
	else if (expanded_args && expanded_args[0] && ft_strncmp(expanded_args[0], "pwd", 4) == 0)
		return (ft_pwd(msh));
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
		ft_printf_error(args[0], ": ", "command not found", "\n");
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
			ft_printf_error(args[0], ": ", "command not found", "\n");
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
	{
		/*the other side of tree wont be executed but if there heredocs fds must be closed*/
		close_hds_rec(ast->right);
		return (status);
	}
	return(execute_ast(msh, ast->right));
}

void	file_open_error(char *filename)
{
	write(2, "msh: ", 6);
	write(2, filename, ft_strlen(filename));
	write(2, ": No such file or directory\n", 28);
}

// int	expand_heredoc(int fd, t_msh *msh)
// {
// 	char *line;
// 	char *filename = gen_name();
	
// 	int new_fd = open(filename, O_RDWR | O_CREAT , 0644);
// 	int new_fd_read = open(filename, O_RDONLY | O_CREAT , 0640);
// 	unlink(filename);
// 	free(filename);
// 	while(1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 			break;
// 		char *tmp = line;
// 		line = expand_here_doc(tmp, msh);
// 		write(new_fd, line, ft_strlen(line));
// 		free(tmp);
// 		free(line);
// 	}
// 	close(fd);
// 	return (new_fd_read);
// }

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
	char	**expanded_args;
	char	**args;
	int		saved_stdin;
	int		saved_stdout;

	if (!ast || !ast->left)
		return (1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (handle_redirections(ast->left, msh))
	{
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	if (ast && ast->right && ast->right->type == BLOCK)
	{
		status = execute_ast(msh, ast->right);
		reset_fd(saved_stdin, saved_stdout);
		return(status);
	}
	args = (char **)ast->right->data;
	expanded_args = expand(args, msh);
	if (expanded_args && expanded_args[0] && !expanded_args[0][0])
	{
		ft_printf_error(expanded_args[0], ": ", "command not found", "\n");
		free_2d_array(expanded_args);
		reset_fd(saved_stdin, saved_stdout);
		close(saved_stdin);
		close(saved_stdout);
		return (127);
	}
	if (expanded_args && is_builtin(expanded_args) == 0)
	{
		status = run_builting(msh, args, expanded_args);
		free_2d_array(expanded_args);
		reset_fd(saved_stdin, saved_stdout);
		return (status);
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
