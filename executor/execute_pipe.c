/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:00:29 by aaitabde          #+#    #+#             */
/*   Updated: 2025/04/10 10:46:41 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void    close_fds(t_ast *ast)
{
    t_reds **reds;

    if (!ast || !ast->left)
        return ;
    reds = (t_reds **)ast->left->data;
    if (!reds)
        return ;
    int i = 0;
    while (reds[i])
    {
        if (reds[i]->fd > 0)
        {
            printf("close\n");
            close(reds[i]->fd);
        }
        i++;
    }
}

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
    close_fds(ast->left);
    close_fds(ast->right);
    if (WTERMSIG(status))
        return (WTERMSIG(status) + 128);
    else
            return(WEXITSTATUS(status));    
}