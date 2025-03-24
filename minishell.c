/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:45:36 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/24 07:34:43 by aaitabde         ###   ########.fr       */
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
	t_msh    msh;
	char    *temp_prompt;
	// atexit(leaks);
	rl_catch_signals = 0;
    (void)ac, (void)av;
    msh.env = build_env(env);
    msh.is_child = false;
	draw_ascii_art();
	while (1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		msh.prompt = readline("msh$ ");
		while (msh.prompt && (ends_with_incomplete_command(msh.prompt) || has_unclosed_parenthesis(msh.prompt)))
		{
			temp_prompt = readline("> ");
			if (temp_prompt)
			{
				char *new_prompt = ft_strjoin(msh.prompt, temp_prompt);
				free(msh.prompt);
				free(temp_prompt);
				msh.prompt = new_prompt;
			}
			else
				break;
		}
		if (!msh.prompt)
            ft_exit(&msh, NULL);
        if (!*msh.prompt)
        {
            free(msh.prompt);
            continue ;
        }
		add_history(msh.prompt);
       	msh.ast = parse(msh.prompt);
        if (!msh.ast)
            continue ;
        process_heredocs(msh.ast, msh.env);
        free_ast(msh.ast);
    }
    clear_env(msh.env);
    rl_clear_history();
}
