/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:04:10 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/09 22:45:34 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*non_interactive_mode(void)
{
	char	*line;
	char	*tmp;

	line = get_next_line(STDIN_FILENO);
	tmp = ft_strtrim(line, "\n \t");
	free(line);
	return (tmp);
}

char	*interactive_mode(void)
{
	char	*line;
	char	*trimmed;
	int		saved_stdout;

	saved_stdout = -1;
	if (!isatty(STDOUT_FILENO))
	{
		saved_stdout = dup(STDOUT_FILENO);
		dup2(STDERR_FILENO, STDOUT_FILENO);
	}
	line = readline("msh$ ");
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
	trimmed = ft_strtrim(line, "\n \t");
	free(line);
	return (trimmed);
}

char	*read_input(t_msh	*msh)
{
	char	*prompt;

	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	if (!isatty(STDIN_FILENO))
		prompt = non_interactive_mode();
	else
		prompt = interactive_mode();
	if (!prompt)
		ft_exit(msh, NULL);
	return (prompt);
}
