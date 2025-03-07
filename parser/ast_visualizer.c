// Centered Tree Visualization for AST

# include <string.h>
# include "parser.h"
// Helper function to convert token key to string representation
const char *token_key_to_string(enum e_token key)
{
    switch(key)
    {
        case AND: return "AND";
        case OR: return "OR";
        case PIPE: return "PIPE";
        case REDIRECT_IN: return "REDIRECT_IN";
        case REDIRECT_OUT: return "REDIRECT_OUT";
        case APPEND: return "APPEND";
        case HERE_DOC: return "HERE_DOC";
        case WORD: return "WORD";
        case WORD_DQ: return "WORD_DQ";
        case WORD_SQ: return "WORD_SQ";
        case WILD_CARD: return "WILD_CARD";
        default: return "COMMAND";
    }
}

// Structure to store node information for visualization
typedef struct s_node_info {
    char *value;
    int position;
    int level;
} t_node_info;

// Calculate the height of the AST
int ast_height(t_ast *root)
{
    if (!root)
        return 0;
    
    int left_height = ast_height(root->left);
    int right_height = ast_height(root->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

// Calculate the total number of nodes in the AST
int count_nodes(t_ast *root)
{
    if (!root)
        return 0;
    
    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

// Get the maximum width needed for a node label
int get_max_label_width(t_ast *root)
{
    if (!root)
        return 0;
    
    int this_width = strlen(token_key_to_string(root->token->key));
    int left_width = get_max_label_width(root->left);
    int right_width = get_max_label_width(root->right);
    
    int max_width = this_width;
    if (left_width > max_width) max_width = left_width;
    if (right_width > max_width) max_width = right_width;
    
    return max_width;
}

// Calculate the horizontal position for each node in a balanced tree layout
void calculate_positions(t_ast *root, t_node_info *nodes, int *index, int level, int left_pos, int right_pos)
{
    if (!root)
        return;
    
    int current = *index;
    (*index)++;
    
    // Calculate middle position
    int position = (left_pos + right_pos) / 2;
    
    // Store node information
    nodes[current].value = strdup(token_key_to_string(root->token->key));
    nodes[current].position = position;
    nodes[current].level = level;
    
    // Process children
    if (root->left || root->right)
    {
        int mid = (left_pos + right_pos) / 2;
        if (root->left)
            calculate_positions(root->left, nodes, index, level + 1, left_pos, mid);
        if (root->right)
            calculate_positions(root->right, nodes, index, level + 1, mid, right_pos);
    }
}

// Function to compare node_info structs for sorting by level
int compare_node_info(const void *a, const void *b)
{
    t_node_info *na = (t_node_info *)a;
    t_node_info *nb = (t_node_info *)b;
    
    if (na->level != nb->level)
        return na->level - nb->level;
    
    return na->position - nb->position;
}

// Print a centered tree representation of the AST
void print_centered_tree(t_ast *root)
{
    if (!root)
    {
        printf("Empty AST\n");
        return;
    }
    
    // Calculate tree dimensions
    int height = ast_height(root);
    int node_count = count_nodes(root);
    int max_width = get_max_label_width(root);
    
    // Create an array to store node information
    t_node_info *nodes = (t_node_info *)malloc(node_count * sizeof(t_node_info));
    if (!nodes)
    {
        printf("Memory allocation failed\n");
        return;
    }
    
    // Calculate display width based on max depth
    int display_width = 80; // Default width
    if (height > 3)
        display_width = 4 * (1 << (height - 1)) * (max_width + 2);
    
    // Calculate positions for each node
    int index = 0;
    calculate_positions(root, nodes, &index, 0, 0, display_width);
    
    // Sort nodes by level for display
    qsort(nodes, node_count, sizeof(t_node_info), compare_node_info);
    
    printf("\n=== AST Visualization ===\n\n");
    
    // Print the tree level by level
    int current_level = 0;
    int start_index = 0;
    
    for (int i = 0; i < node_count; i++)
    {
        if (nodes[i].level > current_level)
        {
            // Print connections for the current level
            char *line = (char *)calloc(display_width + 1, sizeof(char));
            if (!line)
            {
                printf("Memory allocation failed\n");
                break;
            }
            memset(line, ' ', display_width);
            line[display_width] = '\0';
            
            // Draw connections
            for (int j = start_index; j < i; j++)
            {
                int pos = nodes[j].position;
                
                // Draw connection to left child
                for (int k = 0; k < node_count; k++)
                {
                    if (nodes[k].level == current_level + 1)
                    {
                        if (nodes[k].position < pos && nodes[k].position > (pos - 10))
                        {
                            for (int l = nodes[k].position + nodes[k].value[0]; l < pos; l++)
                                line[l] = '-';
                            line[nodes[k].position] = '/';
                        }
                        else if (nodes[k].position > pos && nodes[k].position < (pos + 10))
                        {
                            for (int l = pos + strlen(nodes[j].value); l < nodes[k].position; l++)
                                line[l] = '-';
                            line[nodes[k].position] = '\\';
                        }
                    }
                }
            }
            
            printf("%s\n", line);
            free(line);
            
            // Move to next level
            printf("\n");
            current_level = nodes[i].level;
            start_index = i;
        }
        
        // Print leading spaces
        for (int j = 0; j < nodes[i].position; j++)
            printf(" ");
        
        // Print the node value
        printf("%s", nodes[i].value);
    }
    
    printf("\n\n=========================\n\n");
    
    // Free allocated memory
    for (int i = 0; i < node_count; i++)
        free(nodes[i].value);
    free(nodes);
}

// Advanced visualization with better spacing and connections
void visualize_ast_centered(t_ast *root)
{
    if (!root)
    {
        printf("Empty AST\n");
        return;
    }
    
    // Create a 2D array to hold the tree
    int height = ast_height(root);
    if (height <= 0) {
        printf("Invalid tree height\n");
        return;
    }
    
    int width = (1 << height) * 4; // Width based on potential max nodes
    
    char **tree_display = (char **)malloc((2 * height) * sizeof(char *));
    if (!tree_display)
    {
        printf("Memory allocation failed\n");
        return;
    }
    
    for (int i = 0; i < 2 * height; i++)
    {
        tree_display[i] = (char *)malloc((width + 1) * sizeof(char));
        if (!tree_display[i])
        {
            printf("Memory allocation failed\n");
            // Free previously allocated memory
            for (int j = 0; j < i; j++)
                free(tree_display[j]);
            free(tree_display);
            return;
        }
        // Initialize with spaces
        for (int j = 0; j < width; j++)
            tree_display[i][j] = ' ';
        tree_display[i][width] = '\0';
    }
    
    // Queue for level-order traversal
    typedef struct s_queue_node {
        t_ast *node;
        int level;
        int position;
        struct s_queue_node *next;
    } t_queue_node;
    
    t_queue_node *queue = NULL;
    t_queue_node *tail = NULL;
    
    // Add root to queue
    t_queue_node *root_node = (t_queue_node *)malloc(sizeof(t_queue_node));
    if (!root_node) {
        printf("Memory allocation failed\n");
        for (int i = 0; i < 2 * height; i++)
            free(tree_display[i]);
        free(tree_display);
        return;
    }
    
    root_node->node = root;
    root_node->level = 0;
    root_node->position = width / 2;
    root_node->next = NULL;
    queue = tail = root_node;
    
    // Process the queue
    while (queue)
    {
        // Dequeue
        t_queue_node *current = queue;
        queue = queue->next;
        if (!queue) tail = NULL;
        
        if (!current->node) {
            free(current);
            continue;
        }
        
        // Get the label for the current node
        const char *label = token_key_to_string(current->node->token->key);
        int label_len = strlen(label);
        
        // Calculate position to center the label
        int start_pos = current->position - (label_len / 2);
        if (start_pos < 0) start_pos = 0;
        if (start_pos + label_len >= width) start_pos = width - label_len - 1;
        
        // Add the label to the display
        for (int i = 0; i < label_len && (start_pos + i) < width; i++)
            tree_display[current->level * 2][start_pos + i] = label[i];
        
        // Fixed spacing calculation for deeper trees
        int spacing = width / (2 << (current->level + 1));
        if (spacing < 3) spacing = 3;
        
        // Process left child
        if (current->node->left)
        {
            int child_pos = current->position - spacing;
            if (child_pos < 0) child_pos = 0;
            
            // Draw connection to left child
            int connect_row = current->level * 2 + 1;
            int from_pos = current->position;
            int to_pos = child_pos;
            
            // Draw diagonal line
            for (int i = child_pos; i < from_pos; i++) {
                int y = connect_row;
                int x = i;
                if (i == child_pos)
                    tree_display[y][x] = '/';
                else
                    tree_display[y][x] = '-';
            }
            
            // Enqueue left child
            t_queue_node *left_node = (t_queue_node *)malloc(sizeof(t_queue_node));
            if (left_node) {
                left_node->node = current->node->left;
                left_node->level = current->level + 1;
                left_node->position = child_pos;
                left_node->next = NULL;
                
                if (!queue)
                    queue = tail = left_node;
                else {
                    tail->next = left_node;
                    tail = left_node;
                }
            }
        }
        
        // Process right child
        if (current->node->right)
        {
            int child_pos = current->position + spacing;
            if (child_pos >= width) child_pos = width - 1;
            
            // Draw connection to right child
            int connect_row = current->level * 2 + 1;
            int from_pos = current->position;
            int to_pos = child_pos;
            
            // Draw diagonal line
            for (int i = from_pos + 1; i <= to_pos; i++) {
                int y = connect_row;
                int x = i;
                if (i == to_pos)
                    tree_display[y][x] = '\\';
                else
                    tree_display[y][x] = '-';
            }
            
            // Enqueue right child
            t_queue_node *right_node = (t_queue_node *)malloc(sizeof(t_queue_node));
            if (right_node) {
                right_node->node = current->node->right;
                right_node->level = current->level + 1;
                right_node->position = child_pos;
                right_node->next = NULL;
                
                if (!queue)
                    queue = tail = right_node;
                else {
                    tail->next = right_node;
                    tail = right_node;
                }
            }
        }
        
        free(current);
    }
    
    // Print the tree
    printf("\n==== AST Visualization ====\n\n");
    for (int i = 0; i < 2 * height; i++)
    {
        // Check if line has content
        int has_content = 0;
        for (int j = 0; j < width; j++) {
            if (tree_display[i][j] != ' ') {
                has_content = 1;
                break;
            }
        }
        
        if (!has_content) continue;
        
        // Find start and end positions to trim spaces
        int start = 0;
        while (start < width && tree_display[i][start] == ' ')
            start++;
            
        int end = width - 1;
        while (end >= 0 && tree_display[i][end] == ' ')
            end--;
            
        if (start <= end) {
            for (int j = 0; j < start; j++)
                printf(" ");
            for (int j = start; j <= end; j++)
                printf("%c", tree_display[i][j]);
            printf("\n");
        }
    }
    printf("\n============================\n\n");
    
    // Free allocated memory
    for (int i = 0; i < 2 * height; i++)
        free(tree_display[i]);
    free(tree_display);
}

// Main visualization function that uses the centered approach
void debug_ast_centered(t_ast *root)
{
    visualize_ast_centered(root);
}