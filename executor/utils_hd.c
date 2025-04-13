/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:00:50 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/13 16:33:16 by aalahyan         ###   ########.fr       */
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
	if (!reds)
		return ;
	int i = 0;
	while (reds[i])
	{
		if (reds[i]->type == HEREDOC)
			close(reds[i]->fd);
		i++;
	}
}
void close_hds_rec(t_ast *ast)
{
	if (!ast)
		return ;
	close_hds((t_reds **)ast->data);
	close_hds_rec(ast->left);
	close_hds_rec(ast->right);
}
