/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_leafs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:48:09 by aalahyan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/11 17:56:51 by aalahyan         ###   ########.fr       */
=======
/*   Updated: 2025/03/11 17:53:59 by aaitabde         ###   ########.fr       */
>>>>>>> 4f80f63baa1ca5f48267b135b650faffa67f5ec9
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// void	skip_quotes(char *s, int *i, char c)
// {
// 	(*i)++;
// 	while (s[*i] && s[*i] != c)
// 		(*i)++;
// 	if (s[*i] && s[*i] == c)
// 		(*i)++;
// }

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

char *get_next_cmd(char *s, int *i)
{
    int start;

    while (s[*i])
    {

        while (s[*i] && (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '<' || s[*i] == '>'))
        {
            if (s[*i] == '<' || s[*i] == '>')
            {
                (*i)++;
                while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
                    (*i)++;
                if (s[*i] == '\'' || s[*i] == '"')
                    skip_quotes(s, i, s[*i]);
                else
                    while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '<' && s[*i] != '>')
                        (*i)++;
            }
            else
                (*i)++;
        }
        if (s[*i] && s[*i] != '<' && s[*i] != '>')
        {
            start = *i;
            while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '<' && s[*i] != '>')
            {
                if (s[*i] == '\'' || s[*i] == '"')
                    skip_quotes(s, i, s[*i]);
                else
                    (*i)++;
            }
            return (ft_substr(s, start, *i - start));
        }
    }
    return NULL;
}

int	get_size_2(char *s)
{
	int	i;
	int	size;
	char	*w;
	i = 0;
	size = 0;
	w = get_next_cmd(s, &i);
	while (w)
	{
		free(w);
		w = get_next_cmd(s, &i);
		size++;
	}
	return (size);
}

char	**get_cmd_array(char *s)
{
	char	**arr;
	char	*cmd;
	int		i;
	int		j;

	arr = malloc(sizeof(char *) * (get_size_2(s) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	cmd = get_next_cmd(s, &i);
	while (cmd)
	{
		arr[j++] = cmd;
		cmd = get_next_cmd(s, &i);
	}
	arr[j] = NULL;
	return (arr);
}

void free_2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
	}
	free(arr);
	arr = NULL;
}

t_ast	*get_cmd_node(t_token *token)
{
	t_ast	*node;
	char	**cmd_array;
	cmd_array = get_cmd_array(token->value);
	if (!cmd_array)
		return (NULL);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (free_2d_array(cmd_array), NULL);
	node->data = cmd_array;
	node->left = NULL;
	node->right = NULL;
	node->token = NULL;
	
	return (node);
}

bool	expand_node(t_ast **ast)
{
	(*ast)->left = get_red_node((*ast)->token);
	(*ast)->right = get_cmd_node((*ast)->token);
	return ((*ast)->right);
}

bool	expand_ast_leafs(t_ast *ast)
{
	if ((enum e_red_type)((t_token *)(ast->token)->key) == COMMAND)
	{
		return (expand_node(&ast));
	}
		return (expand_ast_leafs(ast->left) && expand_ast_leafs(ast->right));
	return (true);
}

