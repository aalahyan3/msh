/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:04:10 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/11 23:48:43 by aaitabde         ###   ########.fr       */
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
	
	line = readline("msh$ ");
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
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || !isatty(STDERR_FILENO))
	{
		ft_printf_error("non-interactive mode is not supported!\n", NULL, NULL, NULL);
		msh->is_child = true;
		ft_exit(msh, NULL);
	}
	else
		prompt = interactive_mode();
	optimzed = optimize_prompt(prompt);
	free(prompt);
	prompt = optimzed;
	if (!prompt)
		ft_exit(msh, NULL);
	return (prompt);
}
