/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:27:31 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/10 09:10:18 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*gen_name()
{
	int		i;
	char	*suffix;
	char	*name;

	i = 0;
	while(1)
	{
		suffix = ft_itoa(i);
		name = ft_strjoin("/tmp/heredoc", suffix);
		if (access(name, F_OK) == -1)
			return (free(suffix), name);
		free(suffix);
		free(name);
		i++;
	}
	return (NULL);
}

void	hd_sig_handler(int sig)
{
	struct termios	t;

	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(1);
	}
	else if (sig == SIGQUIT)
	{
		tcgetattr(0, &t);
		t.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &t);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	start_reading(int fd, char *del)
{
	char	*line;
	char	*expanded_del;

	signal(SIGINT, hd_sig_handler);
	signal(SIGQUIT, SIG_IGN);
	expanded_del = expand_quotes_str(del);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, expanded_del) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(expanded_del);
	close(fd);
	exit(0);
}

int	handle_heredoc(t_reds *red)
{
	char	*filename;
	int		fd;
	int		fd_read;
	int		pid;
	int		status;

	filename = gen_name();
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("msh: open");
		free(filename);
		return (1);
	}
	fd_read = open(filename, O_RDONLY);
	if (fd_read == -1)
	{
		perror("msh: open");
		close(fd);
		free(filename);
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		perror("msh: fork");
		close(fd);
		close(fd_read);
		free(filename);
		return (1);
	}
	if (pid == 0)
	{
		start_reading(fd, red->file);
		exit(0);
	}
	close(fd);
	waitpid(pid, &status, 0);
	unlink(filename);
	red->fd = fd_read;
	free(filename);
	return (0);
}


int process_heredocs(t_ast *ast, t_list *env)
{
	t_reds **reds;
	int i;
	int	left;
	int	right;

	i = 0;
	if (!ast)
		return 0;
	if (ast->type == REDIRECTIONS && ast->data)
	{
		reds = (t_reds **)ast->data;
		i = 0;
		while (reds[i])
		{
			if (reds[i]->type == HEREDOC)
			{
				reds[i]->is_hd = 1;
				if (handle_heredoc(reds[i]))
					return (1);
			}
			i++;
		}
	}
	left = process_heredocs(ast->left, env);
	right = process_heredocs(ast->right, env);
	return (left || right);
}

