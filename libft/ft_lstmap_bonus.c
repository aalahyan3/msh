/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:40:37 by aalahyan          #+#    #+#             */
/*   Updated: 2024/12/11 20:58:11 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*clear_and_null(t_list *head, void (*del)(void *))
{
	ft_lstclear(&head, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;
	void	*content;

	if (!lst || !f)
		return (NULL);
	content = f(lst->content);
	head = ft_lstnew(content);
	if (!head || !content)
		return (clear_and_null(head, del));
	lst = lst->next;
	while (lst)
	{
		content = f(lst->content);
		new = ft_lstnew(content);
		if (!new || !content)
			return (clear_and_null(head, del));
		ft_lstadd_back(&head, new);
		lst = lst->next;
	}
	return (head);
}
