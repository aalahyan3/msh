/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 10:16:23 by aalahyan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/03/12 22:22:52 by aalahyan         ###   ########.fr       */
=======
/*   Updated: 2025/03/12 14:36:35 by aaitabde         ###   ########.fr       */
>>>>>>> origin/executer
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
// ls > out1.txt > out2.txt > out3.txt > out4.txt > out5.txt > out6.txt > ou7.txt && echo done | cat -e > result.txt
int main(int ac, char **av, char **env)
{
	char *prompt;
	t_ast *ast;
	t_list	*env_l;

	(void)ac;
	(void)av;
	env_l = build_env(env);
	if (!env_l)
		exit(1);
	draw_ascii_art();
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
		execute_ast(ast, env);
	}
}
