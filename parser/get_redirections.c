/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:15:57 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/17 09:55:37 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_size(char *s)
{
	int		size;
	int		i;
	char	*red;

	size = 0;
	i = 0;
	red = get_next_red(s, &i);
	while (red)
	{
		size++;
		free(red);
		red = get_next_red(s, &i);
	}
	return (size);
}

static enum e_red_type	assign_type(char **s)
{
	if (**s == '<')
	{
		(*s)++;
		if (**s == '<')
		{
			(*s)++;
			return (HEREDOC);
		}
		else
			return (INPUT);
	}
	else if (**s == '>')
	{
		(*s)++;
		if (**s == '>')
		{
			(*s)++;
			return (APPEND);
		}
		else
			return (OUTPUT);
	}
	return (INPUT);
}

static t_reds	*get_red_struct(char *s)
{
	t_reds	*red;

	red = malloc(sizeof(t_reds));
	if (!red)
		return (NULL);
	red->type = assign_type(&s);
	while (*s && ft_isspace(*s))
		s++;
	red->file = ft_strdup(s);
	if (!red->file)
		return (NULL);
	red->fd = -1;
	return (red);
}

static t_reds	**get_reds(char *s)
{
	int		size;
	t_reds	**reds;
	char	*red;
	int		i;
	int		j;

	size = get_size(s);
	if (!size)
		return (NULL);
	reds = malloc(sizeof(t_reds *) * (size + 1));
	if (!reds)
		return (NULL);
	1 && (i = 0, j = 0);
	red = get_next_red(s, &i);
	while (red)
	{
		reds[j] = get_red_struct(red);
		free(red);
		if (!reds[j])
			return (free_red_structs(reds), NULL);
		j++;
		red = get_next_red(s, &i);
	}
	reds[j] = NULL;
	return (reds);
}

t_ast	*get_redirections(char *s)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->content = NULL;
	ast->type = REDIRECTIONS;
	ast->left = NULL;
	ast->right = NULL;
	ast->data = get_reds(s);
	return (ast);
}
