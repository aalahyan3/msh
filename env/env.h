/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitabde <aaitabde@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:19:14 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/14 07:40:17 by aaitabde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>
# include "../libft/libft.h"

struct s_env
{
	char	*key;
	char	*value;
	bool	defined;
};

t_list	*build_env(char **env_array);


#endif