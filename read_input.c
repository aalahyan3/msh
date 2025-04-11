/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:04:10 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/11 17:13:23 by aalahyan         ###   ########.fr       */
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
static int	optimizd_len(char *line)
{
	int		i;
	int		size;

	size = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != SQUOTE_PACEHOLDER && line[i] != DQUOTE_PACEHOLDER && WILDCARD_PACEHOLDER)
			size++;
		i++;
	}
	return (size);
}
static char	*optimize_prompt(char *line)
{
	char	*new;
	int		size;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	size = optimizd_len(line);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] != SQUOTE_PACEHOLDER && line[i] != DQUOTE_PACEHOLDER && WILDCARD_PACEHOLDER)
			new[j++] = line[i];
		i++;
	}
	new[j] = 0;
	return (new);
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
	char	*optimzed;

	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	if (!isatty(STDIN_FILENO))
		prompt = non_interactive_mode();
	else
		prompt = interactive_mode();
	optimzed = optimize_prompt(prompt);
	free(prompt);
	prompt = optimzed;
	if (!prompt)
		ft_exit(msh, NULL);
	return (prompt);
}
