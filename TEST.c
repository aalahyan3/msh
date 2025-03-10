/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 20:10:39 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/10 21:34:23 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
static void	skip_quotes(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
	if (s[*i])
		(*i)++;
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


int main()
{
	printf("%s|\n", ft_strtrim("''", "'"));
}