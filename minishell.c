/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:45:36 by aaitabde          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/10 18:02:09 by aaitabde         ###   ########.fr       */
=======
/*   Updated: 2025/04/10 17:03:01 by aalahyan         ###   ########.fr       */
>>>>>>> 6dc6865d827111b9d51bdde78e0d85f909dae20c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static void draw_ascii_art(void) {
	
	struct winsize w;


	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (w.ws_col <= 75)
		return;
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
