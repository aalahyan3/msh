/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_heredoc_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:36:16 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/06 19:14:20 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	count_hd_2(t_ast *root)
{
	t_reds **reds;
	int		total;
	int		i;

	if (!root)
		return (0);
	total = 0;
	reds = (t_reds **)root->data;
	i = 0;
	if (!reds)
		return (0);
	while (reds[i])
	{
		if (reds[i]->type == HEREDOC)
			total++;
		i++;
	}
	return (total);
}

static int	count_hd(t_ast *root)
{
	int	total;

	total = 0;
	if (!root)
		return (0);
	if (root->type == BLOCK || root->type == COMMAND)
		total = count_hd_2(root->left);
	total += count_hd(root->left);
	total += count_hd(root->right);
	return (total);
}
bool max_heredoc_check(t_ast *root)
{
	int	total;

	total = count_hd(root);
	if (total >= 17)
	{
		ft_printf_error("msh :", "maximum here-document count exceeded\n", NULL, NULL, NULL);
		return (false);
	}
	return (true);
}
