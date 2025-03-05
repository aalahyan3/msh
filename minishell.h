/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:52:40 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/03 01:12:41 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

# include "libft/libft.h"

# define BLUE   "\033[1m\033[36m"
# define RESET  "\033[0m"

enum	e_token
{
	UNASSIGNED,
	OPEN_PARENTHESE,
	CLOSE_PARENTHESE,
	LESS_THAN,
	GREATER_THAN,
	DOUBLE_LESS_THAN,
	DOUBLE_GREATHER_THAN,
	OR,
	AND,
	PIPE,
	COMMAND,
	ARGUMENT,
	INFILE,
	HERE_DOC,
	OUTFILE,
	OUTFILE_APPEND
};

enum e_tok_type
{
	WORD,
	SYMBOL
};

typedef struct s_token
{
	char				*value;
	enum e_token		key;
	enum e_tok_type		type;
}	t_token;

int		main(void);
void	process_prompt(char *prompt);

#endif