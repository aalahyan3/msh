/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:00:29 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/24 20:14:19 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int execute_pipe(t_msh *msh, t_ast *ast)
{
    int        pipefd[2];
    pid_t    pid1;
    pid_t    pid2;
    int        status;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return (1);
    }
    pid1 = fork();
    msh->is_child = true;
    if (pid1 == -1)
    {
        perror("msh: fork");
        return (1);
    }
    if (pid1 == 0)
    {
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execute_ast(msh, ast->left);
        exit(127);
    }
    pid2 = fork();
    if (pid2 == 0)
    {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execute_ast(msh, ast->right);
        exit(0);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, &status, 0);
    if (WTERMSIG(status))
        return (WTERMSIG(status) + 128);
    else
            return(WEXITSTATUS(status));    
}