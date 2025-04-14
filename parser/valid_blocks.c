/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_blocks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:29:20 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/14 13:38:53 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	check_cmd_existance(char *s, int *i)
{
	char	*cmd;

	cmd = get_next_cmd(s, i);
	if (cmd)
	{
		if (*cmd == '|' || *cmd == '&' || *cmd == ';')
		{
			free(cmd);
			return (false);
		}
		ft_putstr_fd("msh: syntax error near unexpected token `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd("'", 2);
		free(cmd);
		return (true);
	}
	return (false);
}

static bool	valid_parentheses(char *s, int *i)
{
	int	expect;

	expect = 1;
	*i += 1;
	while (s[*i] && expect)
	{
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			skip_quotes(s, i, s[*i]);
			continue ;
		}
		if (s[*i] == '(')
			expect += 1;
		if (s[*i] == ')')
			expect -= 1;
		*i += 1;
	}
	if (expect)
	{
		ft_printf_error("syntax error near unclosed parenthisis `(`\n", \
		NULL, NULL, NULL);
		return (false);
	}
	return (true);
}

bool	valid_blocks(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			skip_quotes(s, &i, s[i]);
			continue ;
		}
		if (s[i] == '(')
		{
			if (!valid_parentheses(s, &i))
				return (false);
			if (s[i] && s[i] == '(')
				return (ft_printf_error("syntax error near unexpected token `)\n", \
NULL, NULL, NULL), false);
			if (check_cmd_existance(s, &i))
				return (false);
			continue ;
		}
		i++;
	}
	return (true);
}
