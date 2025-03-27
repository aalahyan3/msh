/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:45:36 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/27 14:05:09 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"


volatile	sig_atomic_t	g_signal_recieved;

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
	t_msh    msh;
	char    *temp_prompt;
	struct termios	terminal;
	//atexit(leaks);
	rl_catch_signals = 0;
    (void)ac, (void)av;
    msh.env = build_env(env);
	increment_shlvl(msh.env);
    msh.is_child = false;
	msh.ast = NULL;
	msh.last_exit = 0;
	draw_ascii_art();
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
