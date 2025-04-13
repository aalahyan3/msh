/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:27:31 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/13 16:07:08 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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

void	start_reading(int fd, char *del, int fd_read)
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
	close(fd_read);
	exit(0);
}

int	init_fds(int *fd, int *fd_read)
{
	char	*file;

	file = gen_name();
	if (!file)
		return (-1);
	*fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0600);
	if (*fd == -1)
	{
		ft_printf_error(file, ": ", strerror(errno), "\n");
		free(file);
		return (-1);
	}
	*fd_read = open(file, O_RDONLY);
	if (*fd_read == -1)
	{
		ft_printf_error(file, ": ", strerror(errno), "\n");
		close(*fd);
		free(file);
		return (-1);
	}
	free(file);
	unlink(file);
	return (0);
}

int	handle_heredoc(t_reds *red, int *stop)
{
	int		fd;
	int		fd_read;
	int		pid;
	int		status;

	if (*stop)
		return (1);
	if (init_fds(&fd, &fd_read) < 0)
		return (1);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		ft_printf_error("fork: ", strerror(errno), "\n", NULL);
		return (close(fd), close(fd_read), 1);
	}
	if (pid == 0)
		start_reading(fd, red->file, fd_read);
	close(fd);
	waitpid(pid, &status, 0);
	*stop = WEXITSTATUS(status);
	if (*stop)
		return (close(fd_read), 1);
	red->fd = fd_read;
	return (0);
}

int	process_heredocs(t_ast *ast, t_list *env, int *stop)
{
	t_reds	**reds;
	int		i;
	int		left;
	int		right;

	if (!ast)
		return (0);
	if (ast->type == REDIRECTIONS && ast->data)
	{
		reds = (t_reds **)ast->data;
		i = 0;
		while (reds[i])
		{
			if (reds[i]->type == HEREDOC)
			{
				reds[i]->is_hd = 1;
				if (handle_heredoc(reds[i], stop))
					return (1);
			}
			i++;
		}
	}
	left = process_heredocs(ast->left, env, stop);
	right = process_heredocs(ast->right, env, stop);
	return (left || right);
}
