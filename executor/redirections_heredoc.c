/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:27:31 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/18 10:41:48 by aaitabde         ###   ########.fr       */
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
		perror("minishell: open");
		if (fd_read != -1)
			close(fd_read);
		free(filename);
		return ;
	}
	unlink(filename);
	if ((red->file[0] == '\'' && red->file[ft_strlen(red->file) - 1] == '\'') || \
	(red->file[0] == '\"' && red->file[ft_strlen(red->file) - 1] == '\"'))
	{
		tmp = red->file;
		red->file = ft_substr(red->file, 1, ft_strlen(red->file) - 2);
		free(tmp);
		expand = 0;
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ((ft_strncmp(line, red->file, ft_strlen(red->file)) == 0) && ft_strlen(red->file) == ft_strlen(line)))
		{
			free(line);
			break ;
		}
		if (expand)
		{
			tmp = line;
			line = expand_here_doc(tmp, ev);
			free(tmp);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(red->file);
	free(filename);
	red->file = ft_strdup(filename);
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
		if (check_syntax(reds))
			return ;
		i = 0;
		while (reds[i])
		{
			if (reds[i]->type == HEREDOC)
				handle_heredoc(reds[i], env);
			i++;
		}
	}
	process_heredocs(ast->left, env);
	process_heredocs(ast->right, env);
}

