/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:55:06 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/03 02:01:21 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int count_special_characters(char *str)
{
    int count = 0;
    while (*str)
    {
        if ((*str == '<' && *(str + 1) == '<') || (*str == '|' && *(str + 1) == '|') || (*str == '>' && *(str + 1) == '>') || (*str == '&' && *(str + 1) == '&'))
        {
            count++;
            str++;
        }
        else if (*str == '(' || *str == ')' || *str == '<' || *str == '>' || *str == '|')
        {
            count++;
        }
        str++;
    }
    return count * 2;
}

static char *expand_prompt(char *str)
{
    int special_chars;
    char *new;
    int i;

    special_chars = count_special_characters(str);
    new = malloc((special_chars + strlen(str) + 1) * sizeof(char));
    if (!new)
        return NULL;
    i = 0;
    while (*str)
    {
        if ((*str == '<' && *(str + 1) == '<') || (*str == '|' && *(str + 1) == '|') || (*str == '>' && *(str + 1) == '>') || (*str == '&' && *(str + 1) == '&'))
        {
            new[i++] = ' ';
            new[i++] = *str++;
            new[i++] = *str;
            new[i++] = ' ';
        }
        else if (*str == '(' || *str == ')' || *str == '<' || *str == '>' || *str == '|')
        {
            new[i++] = ' ';
            new[i++] = *str;
            new[i++] = ' ';
        }
        else
            new[i++] = *str;
        str++;
    }
    new[i] = 0;
    return new;
}

void	process_prompt(char *prompt)
{
	char	*expanded_prompt;

	if (!verify_syntax_quotes(prompt))
	{
		ft_putendl_fd(SYN_ERR, 2);
		return ;
	}
	expanded_prompt = expand_prompt(prompt);
    if (!expanded_prompt)
    {
        ft_putendl_fd("malloc :(", 2);
		return ;
    }
    split_into_tokens(expanded_prompt);
}
