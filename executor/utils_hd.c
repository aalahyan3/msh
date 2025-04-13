/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:00:50 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/13 18:09:42 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*gen_name(void)
{
	int		i;
	char	*suffix;
	char	*name;

	i = 0;
	while (1)
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
	int	i;

	if (!reds)
		return ;
	i = 0;
	while (reds[i])
	{
		if (reds[i]->type == HEREDOC)
			close(reds[i]->fd);
		i++;
	}
}

void	close_hds_rec(t_ast *ast)
{
	if (!ast)
		return ;
	close_hds((t_reds **)ast->data);
	close_hds_rec(ast->left);
	close_hds_rec(ast->right);
}

int	fill_new_hd(int fd, t_reds *red, t_msh *msh)
{
	char	*line;
	char	*expanded;

	line = get_next_line(red->fd);
	while (line)
	{
		expanded = expand_here_doc(line, msh);
		free(line);
		if (!expanded)
			return (0);
		if (*expanded == '\n')
		{
			free(expanded);
			line = get_next_line(red->fd);
			continue ;
		}
		write(fd, expanded, ft_strlen(expanded));
		free(expanded);
		line = get_next_line(red->fd);
	}
	return (1);
}
