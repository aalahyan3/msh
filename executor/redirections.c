/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:10:09 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/16 16:17:27 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	was_hd(t_reds *red, t_msh *msh)
{
	int		fd;
	char	*name;

	if (ft_strchr(red->file, '\'') || ft_strchr(red->file, '"'))
		return (red->fd);
	name = gen_name();
	fd = open(name, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		return (free(name), -1);
	if (!fill_new_hd(fd, red, msh))
	{
		close(fd);
		unlink(name);
		free(name);
		return (-1);
	}
	close(fd);
	fd = open(name, O_RDONLY);
	unlink(name);
	free(name);
	close(red->fd);
	return (fd);
}

int	handle_input(t_reds *red, t_msh *msh, int *in_fd)
{
	char	**filename;

	ft_close(in_fd);
	filename = expand_filename(red->file, msh);
	if (!filename || !*filename[0] || filename[1])
	{
		if (filename && !*filename[0])
			ft_printf_error(filename[0], ": ", \
			"No such file or directory\n", NULL);
		else
			ft_printf_error(red->file, ": ", " ambiguous redirect\n", NULL);
		if (filename)
			free_2d_array(filename);
		return (1);
	}
	*in_fd = open(filename[0], O_RDONLY);
	if (*in_fd < 0)
	{
		ft_printf_error(filename[0], ": ", strerror(errno), "\n");
		free_2d_array(filename);
		return (1);
	}
	free_2d_array(filename);
	return (0);
}

int	handle_output(t_reds *red, t_msh *msh, int *out_fd, int flags)
{
	char	**filename;

	ft_close(out_fd);
	filename = expand_filename(red->file, msh);
	if (!filename || !*filename[0] || filename[1])
	{
		if (filename && !*filename[0])
			ft_printf_error(filename[0], ": ", \
			"No such file or directory\n", NULL);
		else
			ft_printf_error(red->file, ": ", " ambiguous redirect\n", NULL);
		if (filename)
			free_2d_array(filename);
		return (1);
	}
	*out_fd = open(filename[0], flags, 0644);
	if (*out_fd < 0)
	{
		ft_printf_error(filename[0], ": ", strerror(errno), "\n");
		free_2d_array(filename);
		return (1);
	}
	free_2d_array(filename);
	return (0);
}

int	handle_reds(t_reds *red, t_msh *msh, int *in_fd, int *out_fd)
{
	int	flags;

	if (red->type == HEREDOC)
	{
		ft_close(in_fd);
		*in_fd = was_hd(red, msh);
		if (*in_fd < 0)
		{
			ft_close(in_fd);
			return (1);
		}
		return (0);
	}
	else if (red->type == INPUT)
		return (handle_input(red, msh, in_fd));
	else if (red->type == OUTPUT || red->type == APPEND)
	{
		if (red->type == APPEND)
			flags = O_APPEND | O_RDWR | O_CREAT;
		else
			flags = O_TRUNC | O_RDWR | O_CREAT;
		return (handle_output(red, msh, out_fd, flags));
	}
	return (0);
}

int	handle_redirections(t_ast *ast, t_msh *msh)
{
	int		in_fd;
	int		out_fd;
	int		i;
	t_reds	**reds;

	if (!ast->data)
		return (0);
	(1) && (in_fd = -1, out_fd = -1, i = 0, reds = (t_reds **)(ast->data));
	while (reds[i])
	{
		if (handle_reds(reds[i], msh, &in_fd, &out_fd))
		{
			ft_close(&in_fd);
			ft_close(&out_fd);
			close_hds(reds);
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
