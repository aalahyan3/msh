/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:45:36 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/19 15:27:51 by aaitabde         ###   ########.fr       */
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

void adjust_shlvl(t_list *env)
{
	t_list	*tmp;
	char	*tmp1;

// /*adjust_shell_level (change)
//      int change;
// {
//   char new_level[5], *old_SHLVL;
//   intmax_t old_level;
//   SHELL_VAR *temp_var;

//   old_SHLVL = get_string_value ("SHLVL");
//   if (old_SHLVL == 0 || *old_SHLVL == '\0' || legal_number (old_SHLVL, &old_level) == 0)
//     old_level = 0;

//   shell_level = old_level + change;
//   if (shell_level < 0)
//     shell_level = 0;
//   else if (shell_level >= 1000)
//     {
//       internal_warning (_("shell level (%d) too high, resetting to 1"), shell_level);
//       shell_level = 1;
//     }bash impelmetation of adjusting the shelllvl

//   /* We don't need the full generality of itos here. */
//   if (shell_level < 10)
//     {
//       new_level[0] = shell_level + '0';
//       new_level[1] = '\0';
//     }
//   else if (shell_level < 100)
//     {
//       new_level[0] = (shell_level / 10) + '0';
//       new_level[1] = (shell_level % 10) + '0';
//       new_level[2] = '\0';
//     }
//   else if (shell_level < 1000)
//     {
//       new_level[0] = (shell_level / 100) + '0';
//       old_level = shell_level % 100;
//       new_level[1] = (old_level / 10) + '0';
//       new_level[2] = (old_level % 10) + '0';
//       new_level[3] = '\0';
//     }

//   temp_var = bind_variable ("SHLVL", new_level, 
//   */

	tmp = env;
	while(tmp)
	{
		if (ft_strncmp(((struct s_env *)tmp->content)->key, "SHLVL=", 7) == 0)
		{
			tmp1 = ((struct s_env *)tmp->content)->value;
			((struct s_env *)tmp->content)->value = ft_itoa(ft_atoi(tmp1) + 1);
			free(tmp1);
			return;
		}
		tmp = tmp->next;
	}
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
	adjust_shlvl(env_l);
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
		process_heredocs(ast, env_l);
		execute_ast(ast, env_l);
		free_ast(ast);
	}
	clear_env(env_l);
	rl_clear_history();
}
