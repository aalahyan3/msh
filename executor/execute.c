/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:34:24 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/16 12:01:52 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	close_all_hds(t_ast *ast)
{
	int		i;
	t_reds	**reds;

	if (!ast)
		return ;
	close_all_hds(ast->left);
	close_all_hds(ast->right);
	if (!ast || ast->type != REDIRECTIONS || !ast->data)
		return ;
	reds = (t_reds **)ast->data;
	i = 0;
	while (reds[i])
	{
		if (reds[i]->type == HEREDOC)
			ft_close(&reds[i]->fd);
		i++;
	}
}

int	heredoc_handler(t_msh *msh)
{
	int	status;
	int	stop;

	stop = 0;
	status = process_heredocs(msh->ast, msh->env, &stop);
	stop = 0;
	if (status)
		close_all_hds(msh->ast);
	return (status);
}

int	execute(t_msh *msh)
{
	struct termios	original_t;
	int				status;
	struct termios	t;

	tcgetattr(0, &original_t);
	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
	status = heredoc_handler(msh);
	tcsetattr(0, TCSANOW, &original_t);
	if (status)
		return (status);
	return (execute_ast(msh, msh->ast));
}
