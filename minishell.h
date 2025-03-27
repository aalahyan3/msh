/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:52:40 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/27 13:50:20 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

# include "libft/libft.h"
# include "ft_func/ft_func.h"
# include "parser/parser.h"
# include "executor/executor.h"
# include "env/env.h"
# include "expansion/expansion.h"
# include "builtins/builtins.h"
# include <termios.h>
# include "signal_variable.h"


# define BLUE   "\033[1m\033[36m"
# define RESET  "\033[0m"

// enum	e_token
// {
// 	UNASSIGNED,
// 	OPEN_PARENTHESE,
// 	CLOSE_PARENTHESE,
// 	LESS_THAN,
// 	GREATER_THAN,
// 	DOUBLE_LESS_THAN,
// 	DOUBLE_GREATHER_THAN,
// 	OR,
// 	AND,
// 	PIPE,
// 	COMMAND,
// 	ARGUMENT,
// 	INFILE,
// 	HERE_DOC,
// 	OUTFILE,
// 	OUTFILE_APPEND
// };

// enum e_tok_type
// {
// 	WORD,
// 	SYMBOL
// };

// typedef struct s_token
// {
// 	char				*value;
// 	enum e_token		key;
// 	enum e_tok_type		type;
// }	t_token;

// typedef struct s_msh
// {
// 	t_list	*env;
// 	int		last_exit;
// }	t_msh;

// t_ast	*process_prompt(char *prompt);


/*General Utils*/

char	*read_input(t_msh	*msh);


#endif