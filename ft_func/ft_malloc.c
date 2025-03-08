/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:30:36 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/07 17:31:05 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

typedef struct s_mem
{
    void            *ptr;
    struct s_mem    *next;
}   t_mem;

static void ft_free(void *p, int clear)
{
    static t_mem *head = NULL;
    t_mem *temp;

    if (clear)
    {
        while (head)
        {
            temp = head;
            head = head->next;
            free(temp->ptr);
            free(temp);
        }
        return;
    }
    t_mem *new_node = malloc(sizeof(t_mem));
    if (!new_node)
    {
        ft_free(NULL, 1);
        exit(1);
    }
    new_node->ptr = p;
    new_node->next = head;
    head = new_node;
}

void *ft_malloc(size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        ft_free(NULL, 1);
        exit(1);
    }
    ft_free(ptr, 0);
    return ptr;
}

void ft_exit(int n)
{
    ft_free(NULL, 1);
    exit(n);
}
