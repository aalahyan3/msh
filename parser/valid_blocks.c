/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_blocks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:29:20 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/28 17:34:47 by aalahyan         ###   ########.fr       */
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

bool	valid_blocks(char *s)
{
	int		i;
	char	*cmd;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			skip_quotes(s, &i, s[i]);
			continue ;
		}
		if (s[i] == ')')
		{
			i++;
			if (check_cmd_existance(s, &i))
				return (false);
			else
				continue ;
		}
		i++;
	}
	return (true);
}
