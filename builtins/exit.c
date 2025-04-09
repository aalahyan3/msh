/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:41:17 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/09 15:20:09 by aalahyan         ###   ########.fr       */
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
    if (!*arg)
        return (false);
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
    expanded = expand(args, msh);
    if (!expanded || !*expanded[0])
        ft_exit(msh, NULL);
    status = 0;
    over_flowed = false;
    if (!msh->is_child)
        ft_putendl_fd("exit", 2);
    if (expanded[1])
    {
        if (!valid_arg(expanded[1]))
        {
            ft_printf_error("exit :", expanded[1], ": numeric argument required\n", NULL);
            clear_msh(msh);
            free_2d_array(expanded);
            exit(255);
        }
        if (array_size(expanded) > 2)
        {
            ft_printf_error("exit: too many arguments\n", NULL, NULL, NULL);
            free_2d_array(expanded);
            return (1);
        }
        status = get_status(expanded[1], &over_flowed);
        if (over_flowed)
        {
            ft_printf_error("exit :", expanded[1], ": numeric argument required\n", NULL);
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
        clear_msh(msh);
        exit(0);
    }
    return (0);
}
