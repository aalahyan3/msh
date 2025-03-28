/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:42:23 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/28 16:02:19 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	ends_with_incomplete_command(const char *prompt)
{
	size_t len;

	len = strlen(prompt);
	if (len == 0)
		return (0);
	if (prompt[len - 1] == '|' || prompt[len - 1] == '&')
		return (1);
	if (len >= 2 && prompt[len - 1] == '&' && prompt[len - 2] == '&')
		return (1);
	if (len >= 2 && prompt[len - 1] == '|' && prompt[len - 2] == '|')
		return (1);
	return (0);
}

int has_unclosed_parenthesis(const char *prompt)
{
	int open_count;
	int close_count;

	close_count = 0;
	open_count = 0;
	while (*prompt)
	{
		if (*prompt == '(')
			open_count++;
		else if (*prompt == ')')
			close_count++;
		prompt++;
	}
	return (open_count > close_count);
}

char	*interacive_mode(void)
{
	char	*prompt;
	char	*new;
	char	*tmp;
	int		std_out;

	std_out = dup(STDOUT_FILENO);
	if (!isatty(STDOUT_FILENO))
		dup2(STDERR_FILENO, STDOUT_FILENO);
	prompt = readline("msh$ ");
	while (prompt && (ends_with_incomplete_command(prompt) || \
	has_unclosed_parenthesis(prompt)))
	{
		new = readline("> ");
		if (new)
		{
			tmp = ft_strjoin(prompt, new);
			free(prompt);
			free(new);
			prompt = tmp;
		}
		else
			break;
	}
	dup2(std_out, STDOUT_FILENO);
	tmp = ft_strtrim(prompt, "\n \t");
	free(prompt);
	return (tmp);
}
*/
char	*non_interactive_mode(void)
{
	char	*line;
	char	*tmp;
	char	*new;

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

	saved_stdout = dup(STDOUT_FILENO);
	if (!isatty(STDOUT_FILENO))
		dup2(STDERR_FILENO, STDOUT_FILENO);
	line = readline("msh$ ");
	dup2(saved_stdout, STDOUT_FILENO);
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
