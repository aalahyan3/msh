/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:27:31 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/24 05:56:37 by aaitabde         ###   ########.fr       */
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
		i++;
	}
	return (NULL);
}

void handle_heredoc(t_reds *red, t_list *ev)
{
	char	*line;
	char	*filename;
	int		fd;
	int		expand;
	int		fd_read;
	char	*tmp;

	expand = 1;
	filename = gen_name();	
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
	fd_read = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("msh: open");
		if (fd_read != -1)
			close(fd_read);
		free(filename);
		return ;
	}
	unlink(filename);
	if (red->file && red->file[0] && (red->file[0] == '\'' && red->file[ft_strlen(red->file) - 1] == '\'') || \
	(red->file[0] == '\"' && red->file[ft_strlen(red->file) - 1] == '\"'))
	{
		tmp = red->file;
		red->file = ft_substr(red->file, 1, ft_strlen(red->file) - 2);
		free(tmp);
		red->is_hd = 1;
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ((ft_strncmp(line, red->file, ft_strlen(red->file)) == 0) && ft_strlen(red->file) == ft_strlen(line)))
		{
			free(line);
			line = NULL;
			break ;
		}
		if (!*line)
		{
			write(fd, "\n", 1);
			free(line);
			line = NULL;
			continue ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = NULL;
	}
	free(line);
	free(red->file);
	red->file = ft_strdup(filename);
	free(filename);
	close(fd);
	red->fd = fd_read;
	red->type = INPUT;
}

void process_heredocs(t_ast *ast, t_list *env)
{
	t_reds **reds;
	int i;

	i = 0;
	if (!ast)
		return;
	if (ast->type == REDIRECTIONS && ast->data)
	{
		reds = (t_reds **)ast->data;
		i = 0;
		while (reds[i])
		{
			reds[i]->is_hd = 0;
			if (reds[i]->type == HEREDOC)
				handle_heredoc(reds[i], env);
			i++;
		}
	}
	process_heredocs(ast->left, env);
	process_heredocs(ast->right, env);
}

