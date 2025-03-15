/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:27:31 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/15 11:29:44 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void handle_heredoc(t_reds *red)
{
	char *line;
	int fd;
	int fd_read;

	fd = open("/tmp/tmpfile", O_RDWR | O_CREAT | O_TRUNC, 0600);
	fd_read = open("/tmp/tmpfile", O_RDONLY);
	if (fd == -1)
	{
		perror("minishell: open");
		exit(1);
	}
	unlink("/tmp/tmpfile");
	while (1)
	{
		line = readline("> ");
		if (!line || ((ft_strncmp(line, red->file, ft_strlen(red->file)) == 0) && ft_strlen(red->file) == ft_strlen(line)))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(red->file);
	red->file = ft_strdup("/tmp/tmpfile");
	red->fd = fd_read;
	red->type = INPUT;
}


void read_heredoc_input(int fd, const char *delimiter)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void process_heredocs(t_ast *ast)
{
	t_reds **reds;
	int i;

	i = 0;
	if (!ast)
		return;
	if (ast->type == REDIRECTIONS && ast->data)
	{
		reds = (t_reds **)ast->data;
		check_syntax(reds);
		i = 0;
		while (reds[i])
		{
			if (reds[i]->type == HEREDOC)
				handle_heredoc(reds[i]);
			i++;
		}
	}
	process_heredocs(ast->left);
	process_heredocs(ast->right);
}

