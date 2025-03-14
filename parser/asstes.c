/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asstes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 00:03:14 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/14 00:05:29 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_quotes(char *s, int *i, char c)
{
	*i += 1;
	while (s[*i] && s[*i] != c)
		*i += 1;
	if (s[*i])
		*i += 1;
}

void	skip_parentheses(char *s, int *i)
{
	int	expect;

	expect = 1;
	*i += 1;
	while (s[*i] && expect)
	{
		if (s[*i] == '\'' || s[*i] == '\"')
			skip_quotes(s, i, s[*i]);
		if (s[*i] == '(')
			expect += 1;
		if (s[*i] == ')')
			expect -= 1;
		*i += 1;
	}
}