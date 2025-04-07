/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_buff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:59:23 by aalahyan          #+#    #+#             */
/*   Updated: 2025/04/07 21:42:08 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_printf_error(char *s1, char *s2, char *s3, char *s4)
{
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout < 0)
		return ;
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("msh: ");
	if (s1)
		printf("%s", s1);
	if (s2)
		printf("%s", s2);
	if (s3)
		printf("%s", s3);
	if (s4)
		printf("%s", s4);
	dup2(saved_stdout, STDOUT_FILENO);
}