/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:28:02 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/24 22:56:52 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

void free_ast(t_ast **ast)
{
	if (!ast || !*ast)
		return;
	free_ast(&(*ast)->left);
	free_ast(&(*ast)->right);
	(*ast)->left = NULL;
	(*ast)->right = NULL;

	if ((*ast)->data)
	{
		if ((*ast)->type == REDIRECTIONS)
		{
			t_reds **reds = (t_reds **)(*ast)->data;
			free_red_structs(reds);
		}
		else if ((*ast)->type == COMMAND)
		{
			char **args = (char **)(*ast)->data;
			free_2d_array(args);
		}
		(*ast)->data = NULL;
	}
	free((*ast)->content);
	(*ast)->content = NULL;
	free((*ast));
	*ast = NULL;
}
