/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:16:23 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/14 12:43:12 by aaitabde         ###   ########.fr       */
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

void handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void handle_signals(void)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
}

void read_heredoc_input(int fd, const char *delimiter)
{
    char *line;

    while (1)
    {
        // Prompt with a simple "> " prompt.
        line = readline("> ");
        if (!line)
            break;  // End-of-file (Ctrl-D) or error.
        if (strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
}

void process_heredocs(t_ast *ast)
{
	t_red	**reds;

	
	if (!ast)
		return;
	
	if (ast->type == BLOCK)
	{
		if (ast->left && ast->left->data)
		reds = (t_red **)ast->data;
	}
	
    process_heredocs(ast->left);
    process_heredocs(ast->right);
}

void	prepare_heredoc(t_ast *ast)
{
	t_ast	*tmp;
	t_reds	**reds;
}

int main(int ac, char **av, char **env)
{
	char *prompt;
	t_ast *ast;
	t_list	*env_l;

	rl_catch_signals = 0;
	(void)ac;
	(void)av;
	env_l = build_env(env);
	if (!env_l)
		exit(1);
	draw_ascii_art();
	handle_signals();
	while (1)
	{
		prompt = readline("msh$ ");
		if (!prompt || ft_strncmp(prompt, "exit", 4) == 0)
		{
			if(!prompt)
				write(1, "exit\n", 5);
			exit(prompt == NULL);
		}
		add_history(prompt);
		ast = process_prompt(prompt, env_l);
		ast_vis(ast, 0, "");
		process_heredocs(ast);
		execute_ast(ast, env_l);
	}
}
