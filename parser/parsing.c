/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 08:57:28 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/17 10:02:50 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*parse(char *prompt)
{
	t_ast	*ast;

	if (!initial_checks(prompt))
		return (free(prompt), NULL);
	if (!linear_parsing(prompt))
		return (free(prompt), NULL);
	ast = process_prompt(prompt);
	if (!ast)
		return (NULL);
	return (ast);
}
