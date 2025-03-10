// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   quotes_expansion.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/10 21:06:02 by aalahyan          #+#    #+#             */
// /*   Updated: 2025/03/10 21:55:18 by aalahyan         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "parser.h"

// char *get_next_cmd(char *s, int *i)
// {
//     int start;

//     while (s[*i])
//     {

//         while (s[*i] && (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '<' || s[*i] == '>'))
//         {
//             if (s[*i] == '<' || s[*i] == '>')
//             {
//                 (*i)++;
//                 while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
//                     (*i)++;
//                 if (s[*i] == '\'' || s[*i] == '"')
//                     skip_quotes(s, i, s[*i]);
//                 else
//                     while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '<' && s[*i] != '>')
//                         (*i)++;
//             }
//             else
//                 (*i)++;
//         }
//         if (s[*i] && s[*i] != '<' && s[*i] != '>')
//         {
//             start = *i;
//             while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '<' && s[*i] != '>')
//             {
//                 if (s[*i] == '\'' || s[*i] == '"')
//                     skip_quotes(s, i, s[*i]);
//                 else
//                     (*i)++;
//             }
//             return (ft_substr(s, start, *i - start));
//         }
//     }
//     return NULL;
// }

// char	*get_sous_chunk(char *s, int *i)
// {
// 	int	start;

// 	start = *i;
// 	while (s[*i])
// 	{
// 		if (s[*i] == '\'' || s[*i] == '"')
// 		{
// 			skip_quotes(s, i, s[*i]);
// 			return (ft_substr(s, start, *i - start));
// 		}
// 		else
// 		{
// 			while (s[*i] && s[*i] != '\'' && s[*i] != '"')
// 				*i += 1;
// 			return (ft_substr(s, start, *i - start));
// 		}
// 		*i += 1;
// 	}
// 	return (NULL);
// }

// t_list	*get_node_from_chunk(char *chunk)
// {
// 	t_list	*node;
// 	int		i;
// 	char	*s_chunk;
// 	char	*final_string;

// 	i = 0;
// 	node = NULL;
// 	s_chunk = get_sous_chunk(chunk, &i);
// 	while (s_chunk)
// 	{
// 		if (*s_chunk)
// 		{
// 			if (*s_chunk == '\'')
				
// 		}
// 		if (s_chunk[0] == '')
// 	}


// }

// t_list	*get_list_of_args(char *s)
// {
// 	t_list	*head;
// 	t_list	*node;
// 	int		i;
// 	char	*chunk;

// 	i = 0;
// 	head = NULL;
// 	node = NULL;
// 	chunk = get_next_cmd(s, &i);
// 	while (chunk)
// 	{
// 		node = get_node_from_chunk(chunk);
// 	}

// }