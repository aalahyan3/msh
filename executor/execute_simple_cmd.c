/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:16:58 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/24 01:06:41 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void donothing(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit: 3\0", 8);
}

static void handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "bnjnnjn\n", 8);
		exit(130);
	}
}

int	execute_simple_cmd(char *path, char **args, char **env)
{
	pid_t	pid;
	int		status;	

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, donothing);
		execve(path, args, env);
		free(path);
		free_arr(args);
		perror("minishell");
		exit(127);
	}
	else
	{
		free(path);
		free_arr(args);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			return (write(1, "\n", 1), WTERMSIG(status) + 128);
		return (WEXITSTATUS(status));
	}
	return (1);
}
