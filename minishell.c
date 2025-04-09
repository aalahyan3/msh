/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:45:36 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/09 16:40:38 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"



static void draw_ascii_art(void) {
printf("\033[1;33m\n ███▄ ▄███▓ ██▓ ███▄    █  ██▓  ██████  ██░ ██ \
▓█████  ██▓     ██▓    \033[0m\n");
    printf("\033[38;5;220m▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▒\
▓█   ▀ ▓██▒    ▓██▒    \033[0m\n");
    printf("\033[38;5;214m▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██░\
▒███   ▒██░    ▒██░    \033[0m\n");
    printf("\033[38;5;208m▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██ \
▒▓█  ▄ ▒██░    ▒██░    \033[0m\n");
    printf("\033[38;5;202m▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██▓\
░▒████▒░██████▒░██████▒\033[0m\n");
    printf("\033[38;5;166m░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ▒ ▒▓▒ ▒ ░ ▒ ░░▒░▒\
░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░\033[0m\n");
    printf("\033[38;5;130m░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░ \
░ ░  ░░ ░ ▒  ░░ ░ ▒  ░\033[0m\n");
    printf("\033[38;5;94m░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░  \
 ░     ░ ░     ░ ░   \033[0m\n");
    printf("\033[38;5;58m       ░    ░           ░  ░        ░   ░  ░  ░  \
 ░  ░    ░  ░    ░  ░\033[0m\n");
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
	if (!msh->env)
		msh->env = build_default_env();
	if (!*find_in_env("PATH", msh->env))
		ft_lstadd_back(&msh->env, ft_lstnew(make_env_node("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
	if (!msh->env)
		exit (0);
	increment_shlvl(msh->env);
	(void)ac;
	(void)av;
}

int	main(int ac, char **av, char **env)
{
	t_msh			msh;
	struct termios	terminal;

	// atexit(leaks);
	char **test;
	char *exp[20] = {"$hhh", NULL};

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
		msh.ast = parse(msh.prompt, msh.env);
		if (!msh.ast)
			continue ;
		msh.last_exit = execute(&msh);
		tcsetattr(0, TCSANOW, &terminal);
		free_ast(&msh.ast);
	}
	clear_env(msh.env);
	rl_clear_history();
	return (0);
}
