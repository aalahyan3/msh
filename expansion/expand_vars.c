/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_vars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 21:52:33 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/19 20:34:07 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

static int get_size(char **a)
{
	int i;

	i = 0;
	while (a[i])
		i++;
	return (i + 1);
}

char	*find_in_env(char *key, t_list *env)
{
	t_list	*curr;

	curr = env;
	while (curr)
	{
		if (ft_strncmp(key, ((struct s_env *)(curr->content))->key, ft_strlen(key)) == 0 && ft_strlen(key) == ft_strlen(((struct s_env *)(curr->content))->key))
			return ( ((struct s_env *)(curr->content))->value);
		curr = curr->next;
	}
	return ("");
}

char *get_next_var(char *s, int *i, t_list *env_l, bool is_dq)
{
	int start;
	char *v;
	char *t;

	if (!s)
		return (NULL);
	// while (s[*i] && (s[*i] == '\"' || s[*i] == '\''))
	// 	(*i)++;
	start = *i;
	if (s[*i] == '$')
	{
		(*i)++;
		if (!s[*i] && is_dq)
			return (ft_strdup("$"));
		while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
			(*i)++;
		// if (!s[*i])
		// 	return (ft_strdup("$"));
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			*i += ft_strlen(s + *i);
			return (ft_strdup(s));
		}
		if (start == *i)
			return (NULL);
		t = ft_substr(s, start + 1, *i - start - 1);
		if (!t)
			return (NULL);
		v = ft_strdup(find_in_env(t, env_l));
		free(t);
		return (v);
	}
	else
	{
		while (s[*i] && s[*i] != '$')
			(*i)++;
		if (start == *i)
			return (NULL);
		return (ft_substr(s, start, *i - start));
	}
	return (NULL);
}

void expander(char **s, t_list *env_l, bool is_dq)
{
	char	*del;
	char	*var;
	char	*new;
	char	*temp;
	int		i;

	del = "";
	if (**s == '"')
	{
		temp = ft_substr(*s, 1, ft_strlen(*s) - 2);
		free(*s);
		*s = temp;
		del = "\"";
	}
	i = 0;
	new = NULL;
	temp = ft_strjoin(new, del);
	if (!temp)
	{
		free(*s);
		*s = NULL;
		return ;
	}
	new = temp;
	var = get_next_var(*s, &i, env_l, is_dq);
	while (var)
	{
		temp = ft_strjoin(new, var);
		if (!temp)
		{
			free(*s);
			free(new);
			*s = NULL;
			return ;
		}
		free(var);
		new = temp;
		var = get_next_var(*s, &i, env_l, is_dq);
	}
	temp = ft_strjoin(new, del);
	free(new);
	new = temp;
	free(*s);
	*s = new;
}



char	*join_arr(char **arr, bool is_dq)
{
	char	*temp;
	char	*final;
	int		i;

	final = NULL;
	if (is_dq)
	{
		temp = ft_strjoin(final, "\"");
		if (!temp)
			return (free_2d_array(arr), free(final), NULL);
		final = temp;
	}
	i = 0;
	while (arr[i])
	{
		temp = ft_strjoin(final, arr[i]);
		if (!temp)
			return(free_2d_array(arr), free(final), NULL);
		free(final);
		final = temp;
		i++;
	}
	if (is_dq)
	{
		temp = ft_strjoin(final, "\"");
		if (!temp)
			return (free_2d_array(arr), free(final), NULL);
		free(final);
		final = temp;
	}
	free_2d_array(arr);
	return (final);
}

char *expand_str(char *s, t_list *env_l)
{
	char 	**splited;
	int 	i;
	char	*temp;
	bool	is_dq;

	if (!*s)
		return (NULL);
	is_dq = false;
	if (s[0] == '\'' && s[ft_strlen(s) - 1] == '\'')
		return (ft_strdup(s));
	if (s[0] == '"' && s[ft_strlen(s) - 1] == '"')
	{
		is_dq = true;
		temp = ft_substr(s, 1, ft_strlen(s) - 2);
	}
	else
		temp = ft_strdup(s);
	splited = split_by_quotes(temp);
	if (!splited)
		return (NULL);
	i = 0;
	while (splited[i])
	{
		if (*splited[i] != '\'' && ft_strchr(splited[i], '$'))
		{
			expander(&splited[i], env_l, is_dq);
			if (!splited[i])
				return (free_2d_array(splited), NULL);
		}
		i++;
	}
	free(temp);
	return (join_arr(splited, is_dq));
}


char	**expand_vars(char **old, t_list *env_l)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * get_size(old));
	if (!new)
		return (NULL);
	i = 0;
	while (old[i])
	{	
		new[i] = expand_str(old[i], env_l);
		if (!new[i])
			return (free_2d_array(new), NULL);
		i++;
	}
	new[i] = NULL;
	return (split_and_join(new));
}
