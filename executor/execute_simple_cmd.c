/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:16:58 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/09 18:05:26 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void donothing(int sig)
{
	if (sig == SIGQUIT)
		write(1, "Quit: 3\0", 8);
}

int	execute_simple_cmd(char *path, char **args, char **env)
{
	pid_t	pid;
	int		status;	

	pid = fork();
	if (pid < 0)
		((void)perror("fork"), exit(EXIT_FAILURE));
	if (pid == 0)
	{
		signal(SIGQUIT, donothing);
		execve(path, args, env);
		ft_printf_error(path,": ", strerror(errno), "\n");
		free_2d_array(args);
		free_2d_array(env);
		free(path);
		exit(127 - (errno == EACCES));
	}
	else
	{
		free_2d_array(args);
		free(path);
		free_2d_array(env);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			return (write(1, "\n", 1), WTERMSIG(status) + 128);
		return (WEXITSTATUS(status));
	}
	return (1);
}
