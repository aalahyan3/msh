/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:34:24 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/28 21:59:27 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	heredoc_handler(t_msh *msh)
{
	int	std_in;
	int	status;

	std_in = dup(STDIN_FILENO);
	if (std_in < 0)
		return (1);
	status = process_heredocs(msh->ast, msh->env);
	if (status)
		dup2(std_in, STDIN_FILENO);
	close(std_in);
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
