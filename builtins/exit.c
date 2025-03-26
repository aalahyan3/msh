/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:41:17 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/26 04:38:34 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

long    get_status(char *str, bool *overflow)
{
    long long    res;
    long long    sign;

    1 && (sign = 1, res = 0);
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (*str)
    {
        if (res > (LONG_MAX / 10) || (res == (LONG_MAX / 10) && (*str - '0') > (LONG_MAX % 10)))
            *overflow = true;
        res = res * 10 + (*str - 48);
        str++;
    }
    return (res * sign);
}

bool    valid_arg(char *arg)
{
    if (*arg == '-' || *arg == '+')
        arg++;
    while (*arg)
    {
        if (!ft_isdigit(*arg))
            return (false);
        arg++;
    }
    return (true);
}

void    clear_msh(t_msh *msh)
{
    clear_env(msh->env);
    free_ast(&msh->ast);
    rl_clear_history();
}

int    array_size(char **s)
{
    int    i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

int    ft_exit(t_msh *msh, char **args)
{
    long    status;
    bool    over_flowed;
    char    **expanded;

    if(!args)
    {
        if (isatty(STDIN_FILENO))
        {
            ft_putstr_fd("exit\n", 2);   
        }
        clear_msh(msh);
        exit(0);
    }
    if (msh->is_child)
        exit(0);
    expanded = expand(args, msh->env);
    if (!expanded || !*expanded[0])
        ft_exit(msh, NULL);
    status = 0;
    over_flowed = false;
    ft_putendl_fd("exit", 2);
    if (args[1])
    {
        if (!valid_arg(args[1]))
        {
            ft_putstr_fd("msh: exit: ", 2);
            ft_putstr_fd(args[1], 2);
            ft_putendl_fd(": numeric argument required", 2);
            clear_msh(msh);
            free_2d_array(expanded);
            exit(255);
        }
        if (array_size(args) > 2)
        {
            ft_putendl_fd("msh: exit: too many arguments", 2);
            free_2d_array(expanded);
            return (1);
        }
        status = get_status(args[1], &over_flowed);
        if (over_flowed)
        {
            ft_putstr_fd("msh: exit: ", 2);
            ft_putstr_fd(args[1], 2);
            ft_putendl_fd(": numeric argument required", 2);
            clear_msh(msh);
            free_2d_array(expanded);
            exit(255);
        }
        clear_msh(msh);
        free_2d_array(expanded);
        exit(status % 256);
    }
    else
    {
        free_2d_array(expanded);
        exit(0);
    }
    return (0);
}
