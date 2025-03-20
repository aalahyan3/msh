/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:46:00 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/18 19:28:35 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_next_chunk(char *s, int *i)
{
	int	start;

	start = *i;
	while (s[*i])
	{
		if (s[*i] == '<')
		{
			*i += 1;
			if (!s[*i])
				skip_hc(s, i);
		}
		if (s[*i] == '\'')
			skip_quotes(s, i, '\'');
		
	}
}

char	*expand_prompt(char *prompt, t_list *env_l)
{
	char	*expanded_prompt;
	int		i;
	char	*chunk;

	expanded_prompt = NULL;
	i =0;
	chunk = get_next_chunk(prompt, &i);

}