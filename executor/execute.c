/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:34:24 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/27 13:42:33 by aalahyan         ###   ########.fr       */
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
	int				status;


	status = heredoc_handler(msh);	
	if (status)
		return (status);
	return (execute_ast(msh, msh->ast));
}