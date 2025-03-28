/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handeling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:26:25 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/25 21:11:13 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void handle_sig(int sig)
{
	ft_putstr_fd("\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
