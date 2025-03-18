/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builins_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:12:36 by aaitabde          #+#    #+#             */
/*   Updated: 2025/03/18 11:18:16 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int ft_export(char **args, t_list *env)
{
	printf("export\n");
	printf("args[0] = %s\n", args[0]);
	return (0);
}