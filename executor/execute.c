/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:34:24 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/13 14:47:14 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/*
	this may seem inefficiant but it's more better than traversing the tree recursively,
	we know that all herdocs will be taking fd from 3 and so on, max hd is 17.
*/

void	close_all_hds(void)
{
	int	i;

	i = 3;
	while (i <= 17)
		close(i++);
}

int	heredoc_handler(t_msh *msh)
{
	int	status;
	int	stop;

	stop = 0;
	status = process_heredocs(msh->ast, msh->env, &stop);
	stop = 0;
	if (status)
		close_all_hds();
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
