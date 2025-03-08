/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:34:30 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/08 12:03:00 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(char **args, char **env)
{
	int i;
	int n;

	i = 1;
	while (args[i])
		ft_putstr_fd(args[i++], 1);
	(void)env;
	n = 0;
	if (args[1] && ft_strncmp(args[1], "-n\0", 3) == 0)
		n = 1;
	i += (n == 1);
	printf("args[%d] = %s\n", i, args[i]);
	if (!n)
		write(1, "\n", 2);
	return (0);
}
