/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 01:41:17 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/14 14:21:39 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static long	get_status(char *str, bool *overflow)
{
	long long	res;
	long long	sign;

	1 && (sign = 1, res = 0);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (res > (LONG_MAX / 10) \
	|| (res == (LONG_MAX / 10) && (*str - '0') > (LONG_MAX % 10)))
			*overflow = true;
		res = res * 10 + (*str - 48);
		str++;
	}
	return (res * sign);
}

bool	valid_arg(char *arg)
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

static void	exit_overflow(t_msh *msh, char **expanded)
{
	ft_printf_error("exit :", \
	expanded[1], ": numeric argument required\n", NULL);
	clear_msh(msh);
	free_2d_array(expanded);
	exit(255);
}

int	exit_one_arg(t_msh *msh, char **expanded)
{
	bool	over_flowed;
	long	status;

	over_flowed = false;
	if (!valid_arg(expanded[1]))
	{
		ft_printf_error("exit :", \
		expanded[1], ": numeric argument required\n", NULL);
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
		exit_overflow(msh, expanded);
	clear_msh(msh);
	free_2d_array(expanded);
	exit(status % 256);
}

int	ft_exit(t_msh *msh, char **args)
{
	char	**expanded;

	if (!args)
	{
		ft_putstr_fd("exit\n", 2);
		clear_msh(msh);
		exit(0);
	}
	expanded = expand(args, msh);
	if (!expanded || !*expanded[0])
		ft_exit(msh, NULL);
	if (!msh->is_child)
		ft_putendl_fd("exit", 2);
	if (expanded[1])
		return (exit_one_arg(msh, expanded));
	else
	{
		free_2d_array(expanded);
		clear_msh(msh);
		exit(0);
	}
	return (0);
}
