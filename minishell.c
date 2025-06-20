/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:47:15 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/17 10:05:05 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_signal_recieved = 0;

static void	draw_ascii_art(void)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (w.ws_col <= 75)
		return ;
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

static void	setup_msh(t_msh *msh, char **env, char ac, char **av)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) \
	|| !isatty(STDERR_FILENO))
	{
		ft_printf_error("non-interactive mode is not supported!\n", \
		NULL, NULL, NULL);
		exit(1);
	}
	draw_ascii_art();
	(1) && (msh->prompt = NULL, msh->is_child = false, msh->last_exit = 0, \
	msh->ast = NULL, msh->env = build_env(env));
	if (!msh->env)
		msh->env = build_default_env();
	if (!msh->env)
		exit (1);
	handle_var_without_value("OLDPWD", msh->env);
	if (!*find_in_env("PATH", msh->env))
		ft_lstadd_back(&msh->env, \
ft_lstnew(make_env_node("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.")));
	increment_shlvl(msh->env);
	msh->logical_pwd = getcwd(NULL, 0);
	if (!msh->logical_pwd)
		ft_printf_error(NO_PWD_ERR, NULL, NULL, NULL);
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
		add_history(msh.prompt);
		msh.ast = parse(msh.prompt);
		if (!msh.ast)
		{
			msh.last_exit = 2;
			continue ;
		}
		msh.last_exit = execute(&msh);
		tcsetattr(0, TCSANOW, &terminal);
		free_ast(&msh.ast);
	}
	clear_env(msh.env);
	rl_clear_history();
	return (0);
}
