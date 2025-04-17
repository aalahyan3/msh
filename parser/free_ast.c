/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:28:02 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/17 09:57:24 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_red_structs(t_reds **reds)
{
	int	i;

	i = 0;
	while (reds[i])
	{
		free(reds[i]->file);
		reds[i]->file = NULL;
		free(reds[i]);
		reds[i] = NULL;
		i++;
	}
	free(reds);
	reds = NULL;
}

void	free_ast(t_ast **ast)
{
	if (!ast || !*ast)
		return ;
	free_ast(&(*ast)->left);
	free_ast(&(*ast)->right);
	(*ast)->left = NULL;
	(*ast)->right = NULL;
	if ((*ast)->data)
	{
		if ((*ast)->type == REDIRECTIONS)
			free_red_structs((t_reds **)(*ast)->data);
		else if ((*ast)->type == COMMAND)
			free_2d_array((char **)(*ast)->data);
		(*ast)->data = NULL;
	}
	free((*ast)->content);
	(*ast)->content = NULL;
	free((*ast));
	*ast = NULL;
}
