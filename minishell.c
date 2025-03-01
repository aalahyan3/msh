/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:16:23 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/01 14:32:45 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "minishell.h"

int	main(void)
{
	char	*prompt;

	while (1)
	{
		prompt = readline("msh$ ");
		add_history(prompt);
		printf("command line: %s", prompt);
		process_prompt(prompt);
	}
}
