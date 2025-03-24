/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handeling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 11:26:25 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/24 01:03:10 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void handle_sig(int sig)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
