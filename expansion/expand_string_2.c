/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_string_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:40:50 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/21 17:26:49 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "expansion.h"

int	alter_string(char *s)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			skip_quotes(s,&i, s[i]);
			continue ;
		}
		if (s[i] == '*')
		{
			s[i] = WILDCARD_PACEHOLDER;
			res++;
		}
		i++;
	}
	return (res);
}

char	**no_wildcard_case(char *s)
{
	char **arr;

	arr = malloc(sizeof(char *) * 2);
	if (!arr)
		return (NULL);
	arr[0] = expand_quotes(s);
	if (!arr[0])
		return (free_2d_array(arr), NULL);
	arr[1] = NULL;
	return (arr);
}

char	**no_match_case(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == WILDCARD_PACEHOLDER)
			s[i] = '*';
		i++;
	}
	return (no_wildcard_case(s));
}
char	**expand_wildcard(char *s)
{
	int		alter_res;
	char	**res;

	alter_res = alter_string(s);
	if (!alter_res)
		return (no_wildcard_case(s));
	else
		return (wildcard_expander(s));
}


char	**expand_string_2(char *str)
{
	char	**arr;

	if (ft_strchr(str, '*'))
		return (expand_wildcard(str));
	else
		return (no_wildcard_case(str));
}