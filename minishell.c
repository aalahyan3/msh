/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:45:36 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/22 20:31:12 by aalahyan         ###   ########.fr       */
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
void leaks(void)
{
	system("leaks minishell");
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
	// char	**args = malloc(2 * 8);
	// args[0] = ft_strdup("$HOME");
	// args[1] = NULL;
	// char	**res = expand(args, env_l);
	// if (!res)
	// 	printf("err\n");
	// for (int i = 0; res && res[i]; i++)
	// {
	// 	ft_printf("%s\n", res[i]);
	// }
	// free_2d_array(res);
	// free_2d_array(args);
	// clear_env(env_l);
	// exit(1);
	draw_ascii_art();
	handle_signals();
	while (1)
	{
		prompt = readline("msh$ ");
		if (!prompt || ft_strncmp(prompt, "exit", 4) == 0)
		{
			if (!prompt)
				write(1, "exit\n", 5);
			exit(prompt == NULL);
		}
		add_history(prompt);
		ast = parse(prompt, env_l);
		if (!ast)
			continue ;
		process_heredocs(ast, env_l);
		execute_ast(ast, env_l);
		free_ast(ast);
	}
	clear_env(env_l);
	rl_clear_history();
}
