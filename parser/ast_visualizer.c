#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# include "parser.h"
// enum e_token
// {
// 	NONE,//0
// 	BLOCK,//1
// 	PIPE,//2
// 	WORD,//3
// 	WORD_SQ,//4
// 	WORD_DQ,//5
// 	REDIRECT_IN,//6
// 	REDIRECT_OUT,//7
// 	APPEND,//8
// 	HERE_DOC,//9
// 	HERE_DOC_END,//10
// 	AND,//11
// 	OR,//12
// 	WILD_CARD//13
// };

// typedef struct s_token
// {
// 	char				*value;
// 	enum e_token		key;
// }	t_token;

// typedef struct s_ast
// {
// 	t_token				*token;
// 	char				**args;   //ls -la token = ls , args = [ls, -la]
// 	struct s_ast		*left;
// 	struct s_ast		*right;
// }	t_ast;

// Function to get token type as string
char *get_token_type(enum e_token key)
{
    switch (key)
    {
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

// Function to get token symbol
char *get_token_symbol(enum e_token key)
{
    switch (key)
    {
        case PIPE: return "|";
        case REDIRECT_IN: return "<";
        case REDIRECT_OUT: return ">";
        case APPEND: return ">>";
        case HERE_DOC: return "<<";
        case AND: return "&&";
        case OR: return "||";
        default: return NULL;
    }
}



// Function to get node content
char *get_node_content(t_ast *node)
{
    static char buffer[256];
    
    if (!node || !node->token)
        return "NULL";
    
    char *symbol = get_token_symbol(node->token->key);
    if (symbol)
    {
        snprintf(buffer, sizeof(buffer), "[%s]", symbol);
    }
    else if (node->token->value)
    {
        snprintf(buffer, sizeof(buffer), "[%s: %s]", get_token_type(node->token->key), node->token->value);
    }
    else
    {
        snprintf(buffer, sizeof(buffer), "[%s]", get_token_type(node->token->key));
    }
    
    return buffer;
}

// Function to print arguments if they exist
// void print_args(t_ast *node)
// {
//     if (!node || !node->args || !node->args[0])
//         return;
    
//     printf(" args: [");
//     int i = 0;
//     while (node->args[i])
//     {
//         printf("%s", node->args[i]);
//         if (node->args[i + 1])
//             printf(", ");
//         i++;
//     }
//     printf("]");
// }

// Function to calculate the height of the tree
int tree_height(t_ast *root)
{
    if (!root)
        return 0;
    
    int left_height = tree_height(root->left);
    int right_height = tree_height(root->right);
    
    return (left_height > right_height ? left_height : right_height) + 1;
}

// Function to print a horizontal line
void print_hline(int length)
{
    for (int i = 0; i < length; i++)
        printf("-");
}

// Function to print spaces
void print_spaces(int count)
{
    for (int i = 0; i < count; i++)
        printf(" ");
}
// Helper function to fill the matrix with the tree representation
void fill_matrix(char **matrix, t_ast *node, int row, int col, int width)
{
    if (!node || row >= 20)
        return;
    
    // Get node content
    char *content = get_node_content(node);
    int content_len = strlen(content);
    
    // Place the content in the matrix
    for (int i = 0; i < content_len && col + i < width; i++)
        matrix[row][col + i] = content[i];
    
    // Draw vertical line to children if any
    if (node->left || node->right)
        matrix[row + 1][col + content_len/2] = '|';
    
    // Calculate positions for children
    int spacing = 10 * (tree_height(node) - 1);
    if (spacing < 5) spacing = 5;
    
    int left_pos = col - spacing;
    int right_pos = col + spacing;
    
    // Draw horizontal lines to children
    if (node->left)
    {
        for (int i = left_pos + 2; i < col + content_len/2; i++)
            matrix[row + 2][i] = '-';
        matrix[row + 2][left_pos + 1] = '+';
    }
    
    if (node->right)
    {
        for (int i = col + content_len/2 + 1; i < right_pos; i++)
            matrix[row + 2][i] = '-';
        matrix[row + 2][right_pos] = '+';
    }
    
    // Recursively fill in the children
    if (node->left)
        fill_matrix(matrix, node->left, row + 3, left_pos, width);
    
    if (node->right)
        fill_matrix(matrix, node->right, row + 3, right_pos, width);
}
// Function to visualize the tree with proper spacing
void print_tree(t_ast *root, int level, int indent, int is_right)
{
    if (!root)
        return;
    
    const int SPACING = 4;  // Spacing between levels
    const int LINE_LENGTH = 4;  // Length of connecting lines
    
    // Calculate new indent for children
    int new_indent = indent;
    
    // Recursively print right subtree
    print_tree(root->right, level + 1, new_indent + SPACING, 1);
    
    // Print current node
    print_spaces(indent);
    
    if (is_right && level > 0)
    {
        printf("┌");
        print_hline(LINE_LENGTH);
    }
    else if (level > 0)
    {
        printf("└");
        print_hline(LINE_LENGTH);
    }
    
    printf("%s", get_node_content(root));
    // 
    printf("\n");
    
    // Print connecting line for children if needed
    if (root->left && root->right)
    {
        print_spaces(indent + LINE_LENGTH / 2);
        printf("│\n");
    }
    
    // Recursively print left subtree
    print_tree(root->left, level + 1, new_indent + SPACING, 0);
}

// Main visualization function
void ast_v(t_ast *root)
{
    if (!root)
    {
        printf("Empty tree\n");
        return;
    }
    
    printf("\nAST Tree Visualization:\n");
    printf("======================\n\n");
    
    print_tree(root, 0, 0, 0);
    printf("\n");
}

// Another approach: Print the tree level by level with proper spacing
void ast_h(t_ast *root)
{
    if (!root)
    {
        printf("Empty tree\n");
        return;
    }

    // Queue for level-order traversal
    t_ast **queue = malloc(1000 * sizeof(t_ast *));
    if (!queue)
        return;

    int front = 0, rear = 0;
    queue[rear++] = root;
    queue[rear++] = NULL;  // Marker for level end

    int level = 0;
    int max_height = tree_height(root);
    const int NODE_WIDTH = 20;  // Width allocated for each node

    printf("\nHorizontal Tree Layout:\n");
    printf("=====================\n\n");

    while (front < rear)
    {
        t_ast *current = queue[front++];

        if (!current)
        {
            printf("\n\n");  // Double newline between levels
            
            // Print vertical connections between levels
            if (front < rear)
            {
                int nodes_at_next_level = 0;
                int i = front;
                while (i < rear && queue[i] != NULL)
                {
                    nodes_at_next_level++;
                    i++;
                }

                for (int j = 0; j < nodes_at_next_level; j++)
                {
                    print_spaces(NODE_WIDTH / 2 + j * NODE_WIDTH);
                    printf("|\n");
                }
            }

            if (front < rear)
                queue[rear++] = NULL;  // Add marker for the next level
                
            level++;
            continue;
        }

        // Print the node content
        printf("%-*s", NODE_WIDTH, get_node_content(current));

        // Add children to queue
        if (current->left)
            queue[rear++] = current->left;
        if (current->right)
            queue[rear++] = current->right;
    }

    free(queue);
    printf("\n\n");
}

// Final version that combines horizontal and vertical representations
void ast_vw(t_ast *root)
{
    if (!root)
    {
        printf("Empty tree\n");
        return;
    }
    
    // Create a matrix to represent the tree
    const int MAX_HEIGHT = 20;  // Adjust as needed
    const int MAX_WIDTH = 200;  // Adjust as needed
    char **matrix = malloc(MAX_HEIGHT * sizeof(char *));
    
    if (!matrix)
        return;
        
    for (int i = 0; i < MAX_HEIGHT; i++)
    {
        matrix[i] = malloc(MAX_WIDTH * sizeof(char));
        if (!matrix[i])
        {
            for (int j = 0; j < i; j++)
                free(matrix[j]);
            free(matrix);
            return;
        }
        
        // Initialize with spaces
        for (int j = 0; j < MAX_WIDTH; j++)
            matrix[i][j] = ' ';
    }
    
    // Fill the matrix with the tree representation
    int root_pos = MAX_WIDTH / 2;
    fill_matrix(matrix, root, 0, root_pos, MAX_WIDTH);
    
    // Print the matrix
    printf("\nTree Visualization (Wide Format):\n");
    printf("===============================\n\n");
    
    for (int i = 0; i < MAX_HEIGHT; i++)
    {
        int has_content = 0;
        for (int j = 0; j < MAX_WIDTH; j++)
        {
            if (matrix[i][j] != ' ')
            {
                has_content = 1;
                break;
            }
        }
        
        if (!has_content)
            break;
            
        for (int j = 0; j < MAX_WIDTH; j++)
            printf("%c", matrix[i][j]);
        printf("\n");
    }
    
    // Free the matrix
    for (int i = 0; i < MAX_HEIGHT; i++)
        free(matrix[i]);
    free(matrix);
    printf("\n-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n");
}



// Function to demonstrate usage
// void example_usage()
// {
//     // Create a sample tree
//     t_token token_and = {NULL, AND};
//     t_token token_ls = {strdup("ls"), WORD};
//     t_token token_pipe = {NULL, PIPE};
//     t_token token_grep = {strdup("grep"), WORD};
//     t_token token_cat = {strdup("cat"), WORD};
//     
//     char *args_ls[] = {strdup("ls"), strdup("-la"), NULL};
//     char *args_grep[] = {strdup("grep"), strdup("file"), NULL};
//     char *args_cat[] = {strdup("cat"), strdup("file.txt"), NULL};
//     
//     t_ast node_cat = {&token_cat, args_cat, NULL, NULL};
//     t_ast node_grep = {&token_grep, args_grep, NULL, NULL};
//     t_ast node_pipe = {&token_pipe, NULL, &node_cat, &node_grep};
//     t_ast node_ls = {&token_ls, args_ls, NULL, NULL};
//     t_ast node_and = {&token_and, NULL, &node_ls, &node_pipe};
//     
//     // Visualize the tree
//     visualize_ast(&node_and);
//     
//     // Alternative visualization
//     visualize_ast_wide(&node_and);
// }