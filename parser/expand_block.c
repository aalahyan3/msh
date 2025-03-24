/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 02:42:28 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/23 19:59:13 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


char	*get_parenthisis_block(char *s)
{
	int	start;
	int	i;
	int	expected;

	i = 0;
	while (s[i] && s[i] != '(')
	{
		if (s[i] == '\'' || s[i] == '"')
			skip_quotes(s, &i, s[i]);
		else
			i++;
	}
	if (!s[i])
		return (NULL);
	i++;
	start = i;
	expected = 1;
	while (s[i] && expected)
	{
		if (s[i] == '\'' || s[i] == '\"')
			skip_quotes(s, &i, s[i]);
		if (s[i] == '(')
			expected++;
		if (s[i] == ')')
			expected--;
		i++;
	}
	if (expected)
		return (NULL);
	return (ft_substr(s, start, i - start - 1 ));
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

int get_size(char *s)
{
	int 	i;
	int		size;
	char	*cmd;

	i = 0;
	size = 0;
	cmd = get_next_cmd(s, &i);
	while (cmd)
	{
		size++;
		free(cmd);
		cmd = get_next_cmd(s, &i);
	}
	return size;
}

char	**get_command_array(char *s)
{
	int	i;
	int	j;
	int	size;
	char	**array;
	char	*cmd;

	size = get_size(s);
	if (!size)
		return NULL;
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return NULL;
	i = 0;
	j = 0;
	cmd = get_next_cmd(s, &i);
	while (cmd)
	{
		array[j] = cmd;
		j++;
		cmd = get_next_cmd(s, &i);
	}
	array[j] = NULL;
	return array;
}

t_ast	*get_block(char *s)
{
	t_ast	*ast;
	char	*parenthisis_block;

	if (!s || !*s)
		return (NULL);
	parenthisis_block = get_parenthisis_block(s);
	if (parenthisis_block)
		return (process_prompt(parenthisis_block));
	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->content = NULL;
	ast->type = COMMAND;
	ast->data = get_command_array(s);
	ast->left = NULL;
	ast->right = NULL;
	return (ast);
}

t_ast	*expand_block(char *s)
{
	t_ast	*ast;

	if (!s || !*s)
		return (NULL);
	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->content = ft_strdup(s);
	ast->type = BLOCK;
	ast->data = NULL;
	ast->left = get_redirections(s);
	ast->right = get_block(s);
	free(s);
	return (ast);
}