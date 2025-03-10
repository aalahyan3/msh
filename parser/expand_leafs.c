/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_leafs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:48:09 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/10 19:50:09 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	skip_quotes(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
	if (s[*i] && s[*i] == c)
		(*i)++;
}

void	free_red_array(t_red **red)
{
	int	i;

	i = 0;
	while (red[i])
	{
		free(red[i]->name);
		free(red[i]);
		i++;
	}
	free(red);
}

char	*get_next_red(char *s, int *i)
{
	int	start;

	while (s[*i])
	{
		if (s[*i] == '>' || s[*i] == '<')
		{
			start = *i;
			while (s[*i] && (s[*i] == '>' || s[*i] == '<'))
				*i += 1;
			while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
				*i += 1;
			if (s[*i] == '\'' || s[*i] == '"')
				skip_quotes(s, i, s[*i]);
			while (s[*i] && s[*i] != ' ' && s[*i] != '\t')
				*i += 1;
			return (ft_substr(s, start, *i - start));
		}
		*i += 1;
	}
	return (NULL);
}

int	get_size(char *s)
{
	int		i;
	int		size;
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

t_red	*get_red(char *r)
{
	t_red	*red;

	red = malloc(sizeof(t_red));
	if (!red)
		return (NULL);
	if (*r == '>')
	{
		r++;
		if (*r == '>')
		{
			r++;
			red->type = APPEND;
		}
		else
			red->type = OUTPUT;
	}
	else if (*r == '<')
	{
		r++;
		if (*r == '<')
		{
			r++;
			red->type = HERE_DOC;
		}
		else
			red->type = INPUT;
	}
	while (*r && (*r == ' ' || *r == '\t'))
		r++;
	red->name = ft_strdup(r);
	if (!red->name)
		return (free(red), NULL);
	return (red);
}


t_red	**get_red_array(char *s)
{
	int		i;
	int		size;
	t_red	**red;
	char	*r;
	int	j;
	
	size = get_size(s);
	if (!size)
		return (NULL);
	red = malloc(sizeof(t_red *) * (size + 1));
	if (!red)
		return (NULL);
	i = 0;
	j = 0;
	r = get_next_red(s, &i);
	while (r)
	{
		red[j++] = get_red(r);
		if (!red[j - 1])
			return (free_red_array(red), free(r), NULL);
		free(r);
		r = get_next_red(s, &i);
	}
	red[j] = NULL;
	return (red);
}

t_ast	*get_red_node(t_token *tok)
{
	t_ast	*node;
	t_red	**red;
	t_reds	*reds;
	
	reds = malloc(sizeof(t_reds));
	if (!reds)
		return (NULL);
	red = get_red_array(tok->value);
	if (!red)
		return (NULL);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (free_red_array(red), NULL);
	node->data = red;
	node->right = NULL;
	node->left = NULL;
	node->token = NULL;
	return (node);
}
bool	is_meta_char(char c)
{

}

char	*get_next_cmd(char *s, int *i)
{
	int	start;

	while (s[*i])
	{
		while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
			*i += 1;
		if (s[*i] && (s[*i] == '\'' || s[*i] == '"'))
			skip_quotes(s, i, s[*i]);
		if (s[*i] && s[*i] != '>' && s[*i] != '<')
		{
			
		}
	}
}

char	**get_cmd_array(char *s)
{

}

t_ast	*get_cmd_node(t_token *token)
{
	t_ast	*node;
	char	**cmd_array;

	cmd_array = get_cmd_array(token->value);
	if (!cmd_array)
		return (NULL);
}

bool	expand_node(t_ast **ast)
{
	(*ast)->left = get_red_node((*ast)->token);
	if (!(*ast)->left)
		return (false);
	// (*ast)->right = get_cmd_node((*ast)->token);
	// if (!(*ast)->right)
		// return (false);
	return (true);
}

bool	expand_ast_leafs(t_ast *ast)
{
	if ((enum e_red_type)((t_token *)(ast->token)->key) == COMMAND)
	{
		return (expand_node(&ast));
	}
	if (ast->left)
		return (expand_ast_leafs(ast->left));
	if (ast->right)
		return (expand_ast_leafs(ast->right));
	return (true);
}

