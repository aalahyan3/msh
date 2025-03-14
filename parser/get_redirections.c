/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:15:57 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/14 10:21:28 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_next_red(char *s, int *i)
{
	int	start;

	while (s[*i])
	{
		if (s[*i] == '(')
		{
			skip_parentheses(s, i);
			continue;
		}
		if (s[*i]  && s[*i] == '>' || s[*i] == '<')
		{
			while (s[*i] && (s[*i] == '>' || s[*i] == '<'))
				*i += 1;
			while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
				*i += 1;
			start = *i;
			if (s[*i] == '\'' || s[*i] == '"')
				skip_quotes(s, i, s[*i]);
			while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '<' && s[*i] != '>')
				*i += 1;
			return (ft_substr(s, start, *i - start));
		}
		*i += 1;
	}
	return (NULL);
}

static int get_size(char *s)
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

t_reds	*get_red_struct(char *s)
{
	t_reds	*red;

	red = malloc(sizeof(t_reds));
	if (!red)
		return (NULL);
	if (*s == '<')
	{
		s++;
		if (*s == '<')
		{
			red->type = HEREDOC;
			s++;
		}
		else
			red->type = INPUT;
	}
	else if (*s == '>')
	{
		s++;
		if (*s == '>')
		{
			red->type = APPEND;
			s++;
		}
		else
			red->type = OUTPUT;
	}
	red->file = ft_strdup(s);
	red->fd = -1;
	return (red);
}

t_reds	**get_reds(char *s)
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
	i = 0;
	j = 0;
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
