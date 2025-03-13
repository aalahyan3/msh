/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:58:58 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/12 23:46:59 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char *get_next_cmd(char *s, int *i)
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

char	*get_chunk(char *s, int *i)
{
	int	start;

	start = *i;
	if (!s[*i])
		return (NULL);
	if (s[*i] == '$')
	{
		*i += 1;
		while (s[*i] && s[*i] != '$' && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '\'' && s[*i] != '"')
			*i += 1;
		return (ft_substr(s, start, *i - start));
	}
	else
	{
		while (s[*i] && s[*i] != '$')
		{
			if (s[*i] == '\'')
			{
				skip_quotes(s, i, s[*i]);
				continue;
			}
			*i += 1;
		}
		return (ft_substr(s, start, *i - start));
	}
	return (NULL);
}

char	*expand(char *var, t_list *env)
{
	t_list	*curr;
	char	*key;

	curr = env;
	
	while (curr)
	{
		key = ((struct s_env *)(curr->content))->key;
		if (!ft_strncmp(var, key, ft_strlen(key)) && ft_strlen(key) == ft_strlen(var))
			return (((struct s_env *)(curr->content))->value);
		curr = curr->next;
	}
	return (ft_strdup(""));
}
static int	get_size(char *s)
{
	int		i;
	char	*cmd;
	int		size;
	i = 0;
	size = 0;
	cmd = get_next_cmd(s, &i);
	while (cmd)
	{
		size++;
		free(cmd);
		cmd = get_next_cmd(s, &i);
	}
	return (size);
}
char	*expand_var(char *s, t_list *env)
{
	char	*final;
	char	*temp;
	int		i;
	char	*chunk;
	char	*exp;

	final = NULL;
	i = 0;
	chunk = get_chunk(s, &i);
	while (chunk)
	{
		if (*chunk == '$')
		{
			exp = expand(chunk + 1, env);
			if (!exp)
				return (free(final), free(chunk), NULL);
			temp = ft_strjoin(final, exp);
			free(final);
			free(exp);
			if (!temp)
				return (free(chunk), NULL);
			final = temp;
		}
		else
		{
			temp = ft_strjoin(final, chunk);
			free(final);
			free(chunk);
			final = temp;
		}
		chunk = get_chunk(s, &i);
	}
	
	return (final);
}

char	**expand_vars(char *s, t_list *env)
{
	char	*cmd;
	char	**var_expansion;
	char	*expanded;
	int		i;
	int		j;

	if (!get_size(s))
		return (NULL);
	var_expansion = malloc(sizeof(char *) * (get_size(s) + 1));
	if (!var_expansion)
		return (NULL);
	i = 0;
	j = 0;
	cmd = get_next_cmd(s, &i);
	while (cmd)
	{
		expanded =  expand_var(cmd, env);
		free(cmd);
		if (!expanded)
			return (var_expansion[j] = NULL, free_2d_array(var_expansion), NULL);
		if (!*expanded)
		{
			free(expanded);
			cmd = get_next_cmd(s, &i);
			continue ;
		}
		var_expansion[j++] = expanded;
		cmd = get_next_cmd(s, &i);
	}
	var_expansion[j] = NULL;
	return (var_expansion);
}
