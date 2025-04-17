/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:47:27 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/17 10:05:44 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	parse_export_arg(char *arg, t_list *env)
{
	char	*var;
	char	*value;
	char	*equals_pos;
	int		append_mode;

	var = ft_strdup(arg);
	if (!var)
		return ;
	append_mode = 0;
	equals_pos = ft_strchr(var, '=');
	if (equals_pos != NULL)
	{
		if (*(equals_pos - 1) == '+')
			(1) && (append_mode = 1, *(equals_pos - 1) = '\0');
		*equals_pos = '\0';
		value = equals_pos + 1;
		if (append_mode)
			append_to_var(var, value, env);
		else
			handle_var_with_value(var, value, env);
	}
	else
		handle_var_without_value(var, env);
	free(var);
}

/*
void	copy_string_with_quotes(char *new_str, char *value, int *i, int len)
{
	new_str[0] = '"';
	*i = 1;
	while (*i < len)
	{
		new_str[*i] = value[*i - 1];
		(*i)++;
	}
	new_str[*i] = '"';
	new_str[*i + 1] = '\0';
}

void	create_quoted_string(char **str, char *key, char *value)
{
	char	*new_str;
	int		len;
	int		i;

	new_str = malloc(ft_strlen(value) + 3);
	if (!new_str)
	{
		free(key);
		return ;
	}
	len = ft_strlen(value) + 1;
	copy_string_with_quotes(new_str, value, &i, len);
	free(*str);
	*str = ft_strjoin(key, new_str);
	free(key);
	free(new_str);
}

void	inject_quotes(char **str)
{
	char	*key;
	char	*value;

	if (*str[0] == '\0')
		return ;
	value = ft_strchr(*str, '=');
	if (value == NULL)
		return ;
	if (value[1] == '\'' || value[1] == '\"')
		return ;
	value++;
	key = ft_substr(*str, 0, value - *str);
	if (!key)
		return ;
	create_quoted_string(str, key, value);
}

*/

char *get_next_ch(char *s, int *i)
{
	int		start;
	char	*v;
	char*tmp;

	start = *i;
	if (!s[*i])
		return (NULL);
	if (s[*i] == '$')
	{
		*i += 1;
		while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_' || s[*i] == '?'))
			*i += 1;
		v = malloc(sizeof(char) * (*i - start + 3));
		if (!v)
			return (NULL);
		*v = 0;
		ft_strlcat(v, "\"", *i - start + 3);
		tmp = ft_substr(s, start, *i - start);
		if (!tmp)
			return (free(v), NULL);
		ft_strlcat(v, tmp, *i - start + 3);
		free(tmp);
		ft_strlcat(v, "\"", *i - start + 3);
		return (v);
	}
	else
	{
		while (s[*i] && s[*i] != '$')
		{
			if (s[*i] == '\'' || s[*i] == '\"')
			{
				skip_quotes(s, i, s[*i]);
				continue ;
			}
			*i += 1;
		}
		return (ft_substr(s, start, *i - start));
	}
}

char	*inject_quotes(char *str)
{
	char	*var;
	char	*chunk;
	int		i;
	char	*temp;
	char	*final;

	if (!ft_strchr(str, '='))
		return (ft_strdup(str));
	var = ft_strchr(str, '=') + 1;
	i = 0;
	final = ft_substr(str, 0, var - str);
	chunk = get_next_ch(var, &i);
	while (chunk)
	{
		temp = ft_strjoin(final, chunk);
		free(final);
		final = temp;
		free(chunk);
		chunk = get_next_ch(var, &i);
	}
	return (final);
}

int	valid_identifier(char *key)
{
	int	i;

	if (!key || key[0] == '\0' || ft_isdigit(key[0]) \
	|| key[0] == '=' || key[0] == '+')
		return (0);
	i = 0;
	while (key[i] && key[i] != '=')
	{
		if (key[i] == '+' && key[i + 1] == '=')
			return (1);
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
