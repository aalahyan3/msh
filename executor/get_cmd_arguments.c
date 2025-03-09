/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:05:21 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/09 12:24:04 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**get_single_arg(t_ast *ast)
{
	char	**args;

	args = malloc(2 * sizeof(char *));
	if (!args)
		return NULL;
	args[0] = ft_strdup(ast->token->value);
	if (!args[0])
		return (free(args), NULL);
	args[1] = NULL;
	return (args);
}

char	*concatenate_tokens(t_ast *ast)
{
	char	*result;
	char	*tmp;

	result = ft_strdup(ast->token->value);
	if (result == NULL)
		return (NULL);	
	while (ast->right && ast->right->token && \
	ast->right->token->value && ast->right->token->key == WORD)
	{
		tmp = ft_strjoin(result, " ");
		free(result);
		result = ft_strjoin(tmp, ast->right->token->value);
		free(tmp);
		ast = ast->right;
	}
	return (result);
}

char	**get_args(t_ast *ast)
{
	char *concatenated;
	char **args;

	if (!ast || !ast->token || !ast->token->value)
		return NULL;
	if (ast->right && ast->right->token && ast->right->token->value)
	{
		concatenated = concatenate_tokens(ast);\
		if (!concatenated)
			return (NULL);
		args = ft_split(concatenated, ' ');
		if (!args)
			return (NULL);
		free(concatenated);
		return (args);
	}
	else
	{
		args = get_single_arg(ast);
		if (!args)
			return (NULL);
		return (args);
	}
}
