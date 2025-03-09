/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 08:04:07 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/09 11:12:05 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_redirect(t_token *token)
{
	if (token->key == REDIRECT_IN || token->key == REDIRECT_OUT || token->key == APPEND || token->key == HERE_DOC)
		return (true);
	else
		return (false);
}

t_list *grap_redirects(t_list *from)
{
	t_list	*curr;
	t_list	*prev;
	t_token	*new;
	char	*tmp;

	curr = from;
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new ->value = NULL;

	while (curr && ((t_token*)curr->content)->key != OR && ((t_token*)curr->content)->key != AND && ((t_token*)curr->content)->key != PIPE)
	{
		if (is_redirect(curr->content))
		{
			tmp = new->value;
			new->value = ft_strjoin(tmp, ((t_token *)curr->content)->value);
			free(tmp);
			tmp = new->value;
			new->value = ft_strjoin(tmp, ((t_token *)curr->next->content)->value);
			free(tmp);
		}
		curr = curr->next;
	}
	new->key = REDIRECT_IN;
	if (!new->value)
		return (NULL);
	return (new);
}


t_list	*optimize_list(t_list **list)
{
	t_list	*curr;
	t_list	*new;

	while (curr)
	{
		if (!is_redirect(curr->content))
			ft_lstadd_back(&new, ft_lstnew(grap_redirects(&curr)));
	}
}
