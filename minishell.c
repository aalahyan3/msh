/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:45:36 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/26 20:10:30 by aalahyan         ###   ########.fr       */
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
static void handle_ctrl_l()
{
    write(STDOUT_FILENO, "\033[H\033[J", 6);
    write(STDOUT_FILENO, "msh$ ", 5);
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
        process_heredocs(msh.ast, msh.env);
		execute_ast(&msh, msh.ast);
        free_ast(&msh.ast);
		tcsetattr(0, TCSANOW, &terminal);
    }
    clear_env(msh.env);
    rl_clear_history();
}
