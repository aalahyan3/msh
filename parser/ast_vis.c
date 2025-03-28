// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ast_vis.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: aalahyan <aalahyan@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/14 01:41:11 by aalahyan          #+#    #+#             */
// /*   Updated: 2025/03/16 19:47:45 by aalahyan         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "parser.h"

// #define yellow "\033[1m\033[33m"
// #define reset "\033[0m"
// #define blue "\033[1m\033[36m"
// #define red "\033[1m\033[31m"
// #define green "\033[1m\033[32m"

// const char *type_to_string(enum e_tok_type type)
// {
//     switch (type)
//     {
//         case NONE:    return "NONE";
//         case PIPE:    return "PIPE";
//         case OR:      return "OR";
//         case AND:     return "AND";
//         case BLOCK:   return "BLOCK";
//         case COMMAND: return "COMMAND";
//         default:      return "UNKNOWN";
//     }
// }

// void ast_vis_cmd(t_ast *node, int depth, char *prefix)
// {
//     if (!node)
//         return;
//     for (int i = 0; i < depth; i++)
//         printf("\t");
//     printf("%s", prefix);
//     if (!node->data)
//     {
//         printf("null\n" reset);
//     }
//     char **cmd = (char **)node->data;
//     printf(green"command = %s" reset, cmd[0]);
//     for (int i = 1; cmd[i]; i++)
//         printf(yellow" %s", cmd[i]);
//     printf(reset"\n");
// }

// void ast_vis_red(t_ast *node, int depth, char *prefix)
// {
//     if (!node)
//         return;
//     for (int i = 0; i < depth; i++)
//         printf("\t");
//     printf("%s", prefix);
//     if (!node->data)
//     {
//         printf("null\n" reset);
//         return;
//     }
//     t_reds **reds = (t_reds **)node->data;
//     for (int i = 0; reds[i]; i++)
//     {
//         printf(green"file = %s" reset, reds[i]->file);
//     }
//     printf("\n");

// }

// void ast_vis(t_ast *node, int depth, char *prefix)
// {
//     if (node == NULL)
//         return;

//     // Print indentation and prefix
//     for (int i = 0; i < depth; i++)
//         printf("\t");
//     printf("%s", prefix);

//     // Print node details
//     if (node->type == REDIRECTIONS)
//     {
//         printf(red"[redirections] ");
//         if (!node->data)
//         {
//             printf("null\n" reset);
//             return;
//         }
//         t_reds **reds = (t_reds **)node->data;
//         for (int i = 0; reds[i]; i++)
//         {
//             printf(green"file = |%s|" reset, reds[i]->file);
//         }
//         printf("\n" reset);
//     }
//     else if (node->type == BLOCK)
//     {
//         printf(blue"[block]\n" reset);
//         ast_vis(node->left, depth + 1, "L-- ");
//         ast_vis(node->right, depth + 1, "R-- ");
//     }
//     else if (node->type == COMMAND)
//     {
//         printf(yellow"[command] ");
//         if (!node->data)
//         {
//             printf("null\n" reset);
//             return;
//         }
//         char **cmd = (char **)node->data;
//         printf(green"%s " reset, cmd[0]);
//         for (int i = 1; cmd[i]; i++)
//             printf(yellow" %s", cmd[i]);
//         printf(reset"\n");
//     }
//     else
//     {
//         printf("[" green "Type: %s " yellow "Content: %s" reset "]\n",
//             type_to_string(node->type),
//             node->content ? node->content : "null");
//         ast_vis(node->left, depth + 1, "L-- ");
//         ast_vis(node->right, depth + 1, "R-- ");
//     }
//     printf(reset);
// }
