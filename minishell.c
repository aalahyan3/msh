/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:45:36 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/28 19:40:28 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


volatile sig_atomic_t	g_signal_recieved;

static void	draw_ascii_art(void)
{
	printf("\033[38;5;214m            _\
	         _       _            _  _ \n");
	printf(" _ __ ___  (_) _ __  (_) ___ |\
	 |__    ___ | || |\n");
	printf("| '_ ` _ \\ | || '_ \\ | |/ __|| '_ \\  / _ \\| || |\n");
	printf("| | | | | || || | | || |\\__ \\| | | ||  __/| || |\n");
	printf("|_| |_| |_||_||_| |_||_||___/|_| |_| \\___|\
	|_||_| by aalahyan and aaitabde\n\n\033[0m");
}

void	leaks(void)
{
	system("leaks minishell");
}

void	setup_msh(t_msh *msh, char **env, char ac, char **av)
{
	draw_ascii_art();
	msh->prompt = NULL;
	msh->is_child = false;
	msh->last_exit = 0;
	msh->ast = NULL;
	msh->env = build_env(env);
	(void)ac;
	(void)av;
}

int	main(int ac, char **av, char **env)
{
	t_msh			msh;
	struct termios	terminal;

	rl_catch_signals = 0;
	setup_msh(&msh, env, ac, av);
	tcgetattr(0, &terminal);
	while (1)
	{
		msh.prompt = read_input(&msh);
		if (!*msh.prompt)
		{
			free(msh.prompt);
			continue ;
		}
		add_history(msh.prompt);
		msh.ast = parse(msh.prompt);
		if (!msh.ast)
			continue ;
		msh.last_exit = execute(&msh);
		tcsetattr(0, TCSANOW, &terminal);
		free_ast(&msh.ast);
	}
	clear_env(msh.env);
	rl_clear_history();
}
