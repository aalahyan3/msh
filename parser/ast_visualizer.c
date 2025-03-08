#include <stdio.h>
#include <stdlib.h>
# include "parser.h"
// typedef enum e_token
// {
//     NONE,//0
//     BLOCK,//1
//     PIPE,//2
//     WORD,//3
//     WORD_SQ,//4
//     WORD_DQ,//5
//     REDIRECT_IN,//6
//     REDIRECT_OUT,//7
//     APPEND,//8
//     HERE_DOC,//9
//     HERE_DOC_END,//10
//     AND,//11
//     OR,//12
//     WILD_CARD//13
// }    enum e_token_typr;

// typedef struct s_token
// {
//     char                *value;
//     enum e_token        key;
// }    t_token;

// typedef struct s_ast
// {
//     t_token                *token;
//     struct s_ast        *left;
//     struct s_ast        *right;
// }    t_ast;

// Function to convert token type to string
const char *token_type_to_string(enum e_token type) {
    switch (type) {
        case NONE: return "NONE";
        case BLOCK: return "BLOCK";
        case PIPE: return "PIPE";
        case WORD: return "WORD";
        case WORD_SQ: return "WORD_SQ";
        case WORD_DQ: return "WORD_DQ";
        case REDIRECT_IN: return "REDIRECT_IN";
        case REDIRECT_OUT: return "REDIRECT_OUT";
        case APPEND: return "APPEND";
        case HERE_DOC: return "HERE_DOC";
        case HERE_DOC_END: return "HERE_DOC_END";
        case AND: return "AND";
        case OR: return "OR";
        case WILD_CARD: return "WILD_CARD";
        default: return "UNKNOWN";
    }
}

// Function to print the tree horizontally
void print_tree_horizontal_helper(t_ast *root, int space) {
    // Distance between nodes
    int i;
    int count = 10;

    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += count;

    // Process right child first
    print_tree_horizontal_helper(root->right, space);

    // Print current node after space
    printf("\n");
    for (i = count; i < space; i++)
        printf(" ");

    if (root->token) {
        printf("%s", token_type_to_string(root->token->key));
        if (root->token->value) {
            printf(": %s\n", root->token->value);
        } else {
            printf(": NULL\n");
        }
    } else {
        printf("NULL\n");
    }

    // Process left child
    print_tree_horizontal_helper(root->left, space);
}

// Wrapper function to print tree horizontally
void ast_v(t_ast *root) {
    print_tree_horizontal_helper(root, 0);
}

// Example usage (you need to construct your AST)