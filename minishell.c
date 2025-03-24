/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:45:36 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/24 23:32:12 by aalahyan         ###   ########.fr       */
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
// void leaks(void)
// {
// 	system("leaks minishell");
// }

int	ends_with_incomplete_command(const char *prompt)
{
	size_t len;

	len = strlen(prompt);
	if (len == 0)
		return (0);
	if (prompt[len - 1] == '|' || prompt[len - 1] == '&')
		return (1);
	if (len >= 2 && prompt[len - 1] == '&' && prompt[len - 2] == '&')
		return (1);
	if (len >= 2 && prompt[len - 1] == '|' && prompt[len - 2] == '|')
		return (1);
	return (0);
}

int has_unclosed_parenthesis(const char *prompt)
{
	int open_count;
	int close_count;

	close_count = 0;
	open_count = 0;
	while (*prompt)
	{
		if (*prompt == '(')
			open_count++;
		else if (*prompt == ')')
			close_count++;
		prompt++;
	}
	return (open_count > close_count);
}

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void	restore_terminal(int fd)
{
	if (fd != -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

char	*read_prompt(t_msh *msh)
{
	char	*prompt;
	char	*temp_prompt;
	char	*new_prompt;
	int		orig_stdout;
	int		orig_stdin;
	int		orig_stderr;

	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);

	// Save the original file descriptors
	orig_stdout = dup(STDOUT_FILENO);
	orig_stdin = dup(STDIN_FILENO);
	orig_stderr = dup(STDERR_FILENO);

	dup2(STDERR_FILENO, STDOUT_FILENO); 
	if (isatty(STDIN_FILENO))
		write(2, "msh$ ", 5); 
	if (!isatty(STDIN_FILENO))
	{
		prompt = get_next_line(STDIN_FILENO);
	}
	else
	{
		prompt = readline("");
	}
	while (prompt && (ends_with_incomplete_command(prompt) || has_unclosed_parenthesis(prompt)))
	{
		if (!isatty(STDIN_FILENO))
			temp_prompt = get_next_line(STDIN_FILENO);
		else
			temp_prompt = readline("> "); 
		if (temp_prompt)
		{
			new_prompt = ft_strjoin(prompt, temp_prompt);
			free(prompt);
			free(temp_prompt);
			prompt = new_prompt;
		}
		else
			break;
	}
	if (!prompt)
		ft_exit(msh, NULL);
	new_prompt = ft_strtrim(prompt, " \t\n");
	free(prompt);
	dup2(orig_stdout, STDOUT_FILENO);
	dup2(orig_stderr, STDERR_FILENO);
	dup2(orig_stdin, STDIN_FILENO);
	close(orig_stdout);
	close(orig_stderr);
	close(orig_stdin);

	return (new_prompt);
}




int main(int ac, char **av, char **env)
{
	t_msh    msh;
	char    *temp_prompt;
	struct termios	terminal;
	// atexit(leaks);
	rl_catch_signals = 0;
    (void)ac, (void)av;
    msh.env = build_env(env);
    msh.is_child = false;
	msh.ast = NULL;
	draw_ascii_art();
	tcgetattr(0, &terminal);
	while (1)
	{
		signal(SIGINT, handle_sig);
		signal(SIGQUIT, SIG_IGN);
		msh.prompt = read_prompt(&msh);
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
		// tcsetattr(0, TCSANOW, &terminal);
    }
    clear_env(msh.env);
    rl_clear_history();
}
