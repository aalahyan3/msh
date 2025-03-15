/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_error_display.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:30:20 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/15 11:30:30 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	print_type(enum e_red_type s_reds)
{
	write(2, "minishell: syntax error near unexpected token : ", 49);
	if (s_reds == INPUT)
		write(2, "`<'\n", 5);
	else if (s_reds == OUTPUT)
		write(2, "`>'\n", 5);
	else if (s_reds == APPEND)
		write(2, "`>>'\n", 6);
	else if (s_reds == HEREDOC)
		write(2, "`<<'\n", 6);
}

void	check_syntax(t_reds **reds)
{
	int i;

	i = 0;
	while (reds[i])
	{
		if (reds[i]->file[0] == '\0')
		{
			if (reds[i + 1])
				print_type(reds[i + 1]->type);
		}
		i++;
	}
}
