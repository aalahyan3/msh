/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 03:18:01 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/14 03:12:02 by aaitabde         ###   ########.fr       */
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
	return (-1);
}

int	run_builting (char **args, char **env)
{
	if (args && args[0] && ft_strncmp(args[0], "echo", 5) == 0)
 		return (ft_echo(args, env));
	if (args && args[0] && ft_strncmp(args[0], "pwd", 3) == 0)
		return (ft_pwd(env));
	if (args && args[0] && ft_strncmp(args[0], "cd", 2) == 0)
		return (ft_cd(args[1]));
	return (1);
}

int	execute_word(t_ast *ast, char **env)
{
	char	**args;
	char	*path;
	int		i;

	
	if (!ast || !ast->data)
		return (1);
	args = (char **)ast->data;
	if (is_builtin(args) == 0)
		return (run_builting(args, env));
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

int	execute_logic(t_ast *ast, char **env)
{
	int	status;

	status = execute_ast(ast->left, env);
	if ((status != 0 && ast->token->key == AND) || \
		(status == 0 && ast->token->key == OR))
		return (status);
	return(execute_ast(ast->right, env));
}

#include "../minishell.h"
int handle_redirections(t_ast *ast, char **env)
{
	t_red **redirects = (t_red **)ast->left->data;
	int red_count = 0;
	while (redirects[red_count])
		red_count++;
	int fd;
	pid_t pid;
	int status;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return -1;
	}
	if (pid == 0)
	{
		int i = 0;
		while (i < red_count)
		{
			if (redirects[i]->type == HERE_DOC)
			{
				int pipefd[2];
				if (pipe(pipefd) == -1)
				{
					perror("pipe");
					exit(1);//bullshit
				}//bullshit
				char *line;//bullshit
				while (line)//bullshit
				{//bullshit
					line = readline("heredoc> ");//bullshit
					if (ft_strncmp(line, redirects[i]->name, ft_strlen(redirects[i]->name)) == 0 && (ft_strlen(redirects[i]->name) == ft_strlen(line)))//bullshit
						break ;//bullshit
					char *tmp = line;//bullshit
					line = ft_strjoin(line, "\n");//bullshit
					free(tmp);//bullshit
					write(pipefd[1], line, ft_strlen(line));//bullshit
					free(line);//bullshit
				}//bullshit
				free(line);//bullshit
				dup2(pipefd[0], STDIN_FILENO);
				close(pipefd[1]);
			}
			i++;
		}
		i = 0;
		while (i < red_count)
		{
			if (redirects[i]->type == INPUT)
			{
				fd = open(redirects[i]->name, O_RDONLY);
				if (fd < 0)
				{
					write(2, "minishell: ", 11);
					write(2, redirects[i]->name, ft_strlen(redirects[i]->name));
					write(2, ": No such file or directory\n", 28);
					exit(1);
				}
				dup2(fd, STDIN_FILENO);
			}
			else if (redirects[i]->type == OUTPUT)
			{
				fd = open(redirects[i]->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd < 0)
				{
					write(2, "minishell: ", 11);
					write(2, redirects[i]->name, ft_strlen(redirects[i]->name));
					write(2, ": No such file or directory\n", 28);;
					exit(1);
				}
				dup2(fd, STDOUT_FILENO);
			}
			else if (redirects[i]->type == APPEND)
			{
				fd = open(redirects[i]->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd < 0)
				{
					write(2, "minishell: ", 11);
					write(2, redirects[i]->name, ft_strlen(redirects[i]->name));
					write(2, ": No such file or directory\n", 28);
					exit(1);
				}
				dup2(fd, STDOUT_FILENO);
			}
			close(fd);
			i++;
		}
		exit(execute_word(ast->right, env));
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			return -1;
	}
	return 0;
}

int	execute_ast(t_ast *ast, char **env)
{
	if (!ast || !ast->token || !ast->token->key)
		return (1);
	if (ast->token->key == PIPE)
		return (execute_pipe(ast, env));
	if (ast->token->key == AND || ast->token->key == OR)
		return (execute_logic(ast, env));
	if (ast->left)
	{
		if (handle_redirections(ast, env) == -1)
			return (1);
	}
	else
		return (execute_word(ast, env));
}
