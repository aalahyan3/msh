/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putchar_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:40:46 by aalahyan          #+#    #+#             */
/*   Updated: 2024/12/11 21:01:47 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	pf_putchar(char c, int *counter)
{
	int	ret_val;

	if (*counter == -1)
		return ;
	ret_val = (int)write(1, &c, 1);
	if (ret_val == -1)
		(*counter = -1);
	else
		(*counter) += ret_val;
}
