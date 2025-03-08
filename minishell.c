/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:16:23 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/08 07:14:25 by aaitabde         ###   ########.fr       */
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

int main(int ac, char **av, char **env)
{
	char *prompt;
	// int pid;
	t_ast *ast;
	// int status;
	(void)ac;
	(void)av;
	draw_ascii_art();
	while (1)
	{
		prompt = readline(BLUE "msh$ " RESET);
		if (!prompt || ft_strncmp(prompt, "exit", 4) == 0)
			write(1, "THELLA!\n", 8),  exit(prompt == NULL);
		add_history(prompt);
		ast = process_prompt(prompt);
		execute_ast(ast, env);
	}
}
