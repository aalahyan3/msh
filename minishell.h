/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:52:40 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/13 22:07:09 by aalahyan         ###   ########.fr       */
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
# include <sys/ioctl.h>

# include "libft/libft.h"
# include "parser/parser.h"
# include "executor/executor.h"
# include "env/env.h"
# include "expansion/expansion.h"
# include "builtins/builtins.h"
# include <termios.h>

# define NO_PWD_ERR "shell-init: error retrieving \
		current directory: getcwd: cannot access parent \
		directories: No such file or directory\n"

extern volatile int	g_signal_recieved;

char	*read_input(t_msh	*msh);
#endif