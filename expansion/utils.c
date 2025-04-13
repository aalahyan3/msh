/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 20:09:55 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/13 18:35:53 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

char	*find_in_env(char *key, t_list *env)
{
	t_list		*curr;
	size_t		keylen;

	keylen = ft_strlen(key);
	curr = env;
	while (curr)
	{
		if (ft_strncmp(key, ((struct s_env *)(curr->content))->key, keylen) \
		== 0 && keylen == ft_strlen(((struct s_env *)(curr->content))->key))
			return (((struct s_env *)(curr->content))->value);
		curr = curr->next;
	}
	return ("");
}

char	*get_var_name(char *s, int *i)
{
	int		start;

	start = *i;
	*i += 1;
	if (s[*i] == '?')
	{
		*i += 1;
		return (ft_strdup("$?"));
	}
	while (s[*i] && !ft_isalnum(s[*i]) && s[*i] != '_' && s[*i] != '$')
		*i += 1;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
	{
		*i += 1;
		if (s[*i] == '?')
			break ;
	}
	return (ft_substr(s, start, *i - start));
}

void	optimize_wildcard_exp(char **exp)
{
	char			*ptr;
	char			*new;

	ptr = ft_strrchr(*exp, '/');
	if (ptr)
	{
		new = ft_strdup(ptr + 1);
		free(*exp);
		*exp = new;
	}
}

void	sort_array(char **arr)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	alter_var_value(char *var_value)
{
	int		i;

	i = 0;
	while (var_value[i])
	{
		if (var_value[i] == '\'')
			var_value[i] = SQUOTE_PACEHOLDER;
		if (var_value[i] == '\"')
			var_value[i] = DQUOTE_PACEHOLDER;
		i++;
	}
}
