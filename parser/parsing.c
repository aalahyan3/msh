/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 08:57:28 by aalahyan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/13 18:41:21 by aalahyan         ###   ########.fr       */
=======
/*   Updated: 2025/04/13 20:18:35 by aaitabde         ###   ########.fr       */
>>>>>>> d8668caa3dca19285ffd9618bae3cc73db0e33a6
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse(char *prompt, t_list *env)
{
	t_ast	*ast;

	if (!initial_checks(prompt))
		return (free(prompt), NULL);
	if (!linear_parsing(prompt))
		return (free(prompt), NULL);
	ast = process_prompt(prompt);
	if (!ast)
		return (NULL);
	if (!max_heredoc_check(ast))
	{
		free_ast(&ast);
		clear_env(env);
		rl_clear_history();
		exit(2);
	}
	return (ast);
}
