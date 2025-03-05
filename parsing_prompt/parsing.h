/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 11:30:34 by aalahyan          #+#    #+#             */
/*   Updated: 2025/03/03 00:18:57 by aalahyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"


# define SYN_ERR "msh: syntax error!"

void	process_prompt(char *prompt);
bool	verify_syntax_quotes(char *str);
char	**ft_split_msh(char const *s);
int		split_into_tokens(char *prompt);
char	**get_token_array(char *cmd);


# endif