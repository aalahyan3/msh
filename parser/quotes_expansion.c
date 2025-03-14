// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   quotes_expansion.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/10 21:06:02 by aalahyan          #+#    #+#             */
// /*   Updated: 2025/03/10 21:55:18 by aalahyan         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

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




char	**get_cmd_arr(char *s, t_list *env)
{
	char	**expanded_vars;

	expanded_vars = expand_vars(s, env);
	if (!expanded_vars)
		return (NULL);
	return (expanded_vars);
}