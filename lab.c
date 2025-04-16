/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lab.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:21:29 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/16 18:47:22 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <string.h>
#include <ctype.h>
#include "libft/libft.h"

void	skip_quotes(char *s, int *i, char c)
{
	*i += 1;
	while (s[*i] && s[*i] != c)
		*i += 1;
	if (s[*i])
		*i += 1;
}
char	*get_next_ch(char *s, int *i)
{
	int	start;
	char	*v;
	char	*tmp;

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

	var = (strchr(str, '=') + 1);
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

int	main()
{
	char s[100] = "var=$al'$HHH'ddd";

	char *new = inject_quotes(s);
	printf("%s\n", new);
}