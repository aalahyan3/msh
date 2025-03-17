/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 19:53:51 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/17 03:07:12 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "../env/env.h"
# include "../ft_func/ft_func.h"
# include "../parser/parser.h"

char	**expand_vars(char **old, t_list *env_l);
char	**expand(char **arr, t_list *env_l);
char	**split_by_quotes(char *s);
char	**split_not_quotes(char *cmd);
char	**split_msh(char const *s);
char	**split_and_join(char **arr);


#endif