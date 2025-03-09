/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 20:48:09 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/09 09:39:45 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	skip_quotes(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
	if (s[*i])
		(*i)++;
}


char	*get_all_redirections(char *input, int *i)
{
	int		curr_i;

	curr_i = *i + 1;
	while (input[curr_i])
	{
		if (input[*i] == '\'' || input[*i] == '"')
			skip_quotes(input, i, input[*i]);
		if (input[curr_i] == '|' || input[curr_i] == '&')
			break;
		if (input[curr_i] == ' ' || input[curr_i] == '\t')
		{
			while (input[curr_i] && (input[curr_i] == ' ' || input[curr_i] == '\t'))
				curr_i++;
			if (input[curr_i] && input[curr_i] != '<' && input[curr_i] != '>')
				break ;
		}
		curr_i++;
	}
	return (ft_substr(input, *i, curr_i - *i));
}

char	*get_last_hd(char *s, int *i)
{
	int	start;

	(*i)++;
	start = *i;
	// printf("%c\n", s[*i]);
	while(s[*i])
	{
		if (s[*i] == '\'' || s[*i] == '"')
			skip_quotes(s, i, s[*i]);
		if (s[*i] == ' ' || s[*i] == '\t')
		{
			while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
				(*i)++;
		}
		if (s[*i] && s[*i] == '<' && s[*i+1] && s[*i+1] == '<')
		{
			(*i)++;
			// printf("will");
			return (get_last_hd(s, i));
		}
		if (s[*i] == '|' || s[*i] == '&' || s[*i] == '>')
			break ;
		(*i)++;
	}
	return (ft_substr(s, start, *i - start));
}

// int main()
// {
// 	// test hc
// 	char *input = "<<'text<<'lsls >>ls&&";
// 	int i = 0;
// 	printf("%s_\n", get_all_redirections(input, &i));
// }
