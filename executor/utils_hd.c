/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:00:50 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/13 16:01:10 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*gen_name(void)
{
	int		i;
	char	*suffix;
	char	*name;

	i = 0;
	while (1)
	{
		suffix = ft_itoa(i);
		name = ft_strjoin("/tmp/heredoc", suffix);
		if (access(name, F_OK) == -1)
			return (free(suffix), name);
		free(suffix);
		free(name);
		i++;
	}
	return (NULL);
}
