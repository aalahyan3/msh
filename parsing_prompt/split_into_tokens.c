/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_into_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:07:10 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/03 02:34:48 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	print_res(t_token **tokens)
{
	for (int i = 0; tokens[i];i++)
	{
		ft_printf("%-10s => ", tokens[i]->value);
		switch (tokens[i]->key)
		{
		case OPEN_PARENTHESE:
			printf("open (\n");
			break;
		case CLOSE_PARENTHESE:
			printf("close )\n");
			break;
		case LESS_THAN:
			printf("less than\n");
			break;
		case GREATER_THAN:
			printf("greater than\n");
			break;
		case DOUBLE_LESS_THAN:
			printf("double less than\n");
			break;
		case DOUBLE_GREATHER_THAN:
			printf("double greater than\n");
			break;
		case OR:
			printf("or\n");
			break;
		case AND:
			printf("and\n");
			break;
		case PIPE:
			printf("pipe\n");
			break;
		case COMMAND:
			printf("command\n");
			break;
		case ARGUMENT:
			printf("argument\n");
			break;
		case INFILE:
			printf("infile\n");
			break;
		case HERE_DOC:
			printf("here doc\n");
			break;
		case OUTFILE:
			printf("outfile\n");
			break;
		case OUTFILE_APPEND:
			printf("outfile append\n");
			break;
		default:
			printf("unassigned\n");
			break;
		}
	}
}

static int	get_nb_tok(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i + 1);
}


int	split_into_tokens(char *prompt)
{
	char	**token_arr;
	int		i;
	t_token	**tokens;

	token_arr = get_token_array(prompt);
	if (!token_arr)
	{
		ft_putendl_fd("malloc", 1);
		free(prompt);
		return 0;
	}
	free(prompt);
	i = 0;
	tokens = malloc(sizeof(t_token *) * get_nb_tok(token_arr));
	if (!tokens)
	{
		ft_putendl_fd("malloc", 2);
		// free_splited_arr
		return 0;
	}
	while (token_arr[i])
	{
		tokens[i] = malloc(sizeof(t_token));
		if (!tokens[i])
		{
			tokens[i] = NULL;
			// free_tokens(tokens);
			// free_splited_array(token_arr);
			return 1;
		}
		tokens[i]->value = token_arr[i];
		if (!ft_strncmp(token_arr[i], "<", 2))
			tokens[i]->key = LESS_THAN;
		else if (!ft_strncmp(token_arr[i], ">", 2))
			tokens[i]->key = GREATER_THAN;
		else if (!ft_strncmp(token_arr[i], "|", 2))
			tokens[i]->key = PIPE;
		else if (!ft_strncmp(token_arr[i], "(", 2))
			tokens[i]->key = OPEN_PARENTHESE;
		else if (!ft_strncmp(token_arr[i], ")", 2))
			tokens[i]->key = CLOSE_PARENTHESE;
		else if (!ft_strncmp(token_arr[i], "||", 3))
			tokens[i]->key = OR;
		else if (!ft_strncmp(token_arr[i], "&&", 3))
			tokens[i]->key = AND;
		else if (!ft_strncmp(token_arr[i], "<<", 3))
			tokens[i]->key = DOUBLE_LESS_THAN;
		else if (!ft_strncmp(token_arr[i], ">>", 3))
			tokens[i]->key = DOUBLE_GREATHER_THAN;
		else if (i == 0)
			tokens[i]->key = COMMAND;
		else if (i && !ft_strncmp(token_arr[i - 1], "<", 2))
			tokens[i]->key = INFILE;
		else if (i && !ft_strncmp(token_arr[i - 1], ">", 2))
			tokens[i]->key = OUTFILE;
		else if (i && (tokens[i - 1]->key == COMMAND || tokens[i - 1]->key == ARGUMENT))
			tokens[i]->key = ARGUMENT;
		else if (i && tokens[i - 1]->key == INFILE)
			tokens[i]->key = COMMAND;
		else if (i && tokens[i - 1]->key == PIPE)
			tokens[i]->key = COMMAND;
		else if (i && tokens[i - 1]->key == OR)
			tokens[i]->key = COMMAND;
		else if (i && tokens[i - 1]->key == AND)
			tokens[i]->key = COMMAND;
		else if (i && tokens[i - 1]->key == DOUBLE_LESS_THAN)
			tokens[i]->key = HERE_DOC;
		else if (i && tokens[i - 1]->key == OUTFILE)
			tokens[i]->key = OUTFILE_APPEND;
		else if(i && tokens[i - 1]->key == OPEN_PARENTHESE)
			tokens[i]->key = COMMAND;
		else if(i && tokens[i - 1]->key == HERE_DOC)
			tokens[i]->key = COMMAND;
		else
			tokens[i]->key = UNASSIGNED;
		i++;
	}
	tokens[i] = NULL;
	print_res(tokens);
	return 1;
}
