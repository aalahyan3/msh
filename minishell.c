/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:45:36 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/24 06:00:00 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void draw_ascii_art(void)
{
	
	ft_printf("\033[38;5;214m            _         _       _            _  _ \n");
	ft_printf(" _ __ ___  (_) _ __  (_) ___ | |__    ___ | || |\n");
	ft_printf("| '_ ` _ \\ | || '_ \\ | |/ __|| '_ \\  / _ \\| || |\n");
	ft_printf("| | | | | || || | | || |\\__ \\| | | ||  __/| || |\n");
	ft_printf("|_| |_| |_||_||_| |_||_||___/|_| |_| \\___||_||_| by aalahyan and aaitabde\n\n"RESET);
}

// void	leaks(void) __attribute__((destructor));
// void leaks(void)
// {
// 	system("leaks minishell");
// }

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

int main(int ac, char **av, char **env)
{
	char *prompt;
	t_ast *ast;
	t_list	*env_l;
	char *temp_prompt;

	// atexit(leaks);
	rl_catch_signals = 0;
	(void)ac;
	(void)av;
	env_l = build_env(env);
	draw_ascii_art();
	while (1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		prompt = readline("msh$ ");
		if (!prompt || ft_strncmp(prompt, "exit", 4) == 0)
		{
			if (!prompt)
				write(1, "exit\n", 5);
			exit(prompt == NULL);
		}
		while (prompt && (ends_with_incomplete_command(prompt) || has_unclosed_parenthesis(prompt)))
		{
			temp_prompt = readline("> ");
			if (temp_prompt)
			{
				char *new_prompt = ft_strjoin(prompt, temp_prompt);
				free(prompt);
				free(temp_prompt);
				prompt = new_prompt;
			}
			else
				break;
		}
		add_history(prompt);
		ast = parse(prompt);
		if (!ast)
			continue ;
		process_heredocs(ast, env_l);
		execute_ast(ast, env_l);
		free_ast(ast);
	}
	clear_env(env_l);
	rl_clear_history();
}
