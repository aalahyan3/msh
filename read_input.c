/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:04:10 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/16 11:33:38 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sig(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_recieved = 1;
}

static int	optimizd_len(char *line)
{
	int		i;
	int		size;

	size = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != SQUOTE_PACEHOLDER && line[i] != \
		DQUOTE_PACEHOLDER && WILDCARD_PACEHOLDER)
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
		if (line[i] != SQUOTE_PACEHOLDER && line[i] != \
		DQUOTE_PACEHOLDER && WILDCARD_PACEHOLDER)
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
	prompt = interactive_mode();
	optimzed = optimize_prompt(prompt);
	free(prompt);
	prompt = optimzed;
	if (!prompt)
		ft_exit(msh, NULL);
	if (g_signal_recieved)
	{
		msh->last_exit = 1;
		g_signal_recieved = 0;
	}
	if (!*prompt)
	{
		free(prompt);
		return (read_input(msh));
	}
	return (prompt);
}
