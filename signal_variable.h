/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_variable.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:21:16 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/28 16:01:01 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_VARIABLE_H
# define SIGNAL_VARIABLE_H

# include <signal.h>

extern volatile sig_atomic_t	g_signal_recieved;

#endif