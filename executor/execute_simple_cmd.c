/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:16:58 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/09 14:38:31 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		execve(path, args, env);
		free(path);
		free_arr(args);
		perror("minishell");
		exit(127);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return 1;
}
