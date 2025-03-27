#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <termios.h>
#include <unistd.h>

#define END_MARKER "."

volatile sig_atomic_t keep_running = 1;

void sigint_handler(int sig) {
    (void)sig; // Silence unused parameter warning
    printf("\nProcess interrupted. Stopping input...\n");
    keep_running = 0;
}

void reset_terminal_settings() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHO | ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int main() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    char *input;
    size_t heredoc_size = 1024;
    char *heredoc = malloc(heredoc_size);
    if (!heredoc) {
        perror("Unable to allocate memory");
        exit(EXIT_FAILURE);
    }
    heredoc[0] = '\0';

    // Set up signal handler for SIGINT (Ctrl + C)
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        free(heredoc);
        exit(EXIT_FAILURE);
    }

    printf("Enter your heredoc (end with a single period on a new line):\n");

    while (keep_running && (input = readline("> ")) != NULL) {
        if (strcmp(input, END_MARKER) == 0) {
            free(input);
            break;
        }

        size_t input_len = strlen(input);
        size_t current_len = strlen(heredoc);
        if (current_len + input_len + 2 > heredoc_size) {
            heredoc_size *= 2;
            heredoc = realloc(heredoc, heredoc_size);
            if (!heredoc) {
                perror("Unable to reallocate memory");
                free(input);
                exit(EXIT_FAILURE);
            }
        }

        strcat(heredoc, input);
        strcat(heredoc, "\n");
        free(input);
    }

    reset_terminal_settings();

    if (keep_running) {
        printf("Heredoc received:\n%s", heredoc);
    }

    free(heredoc);

    return 0;
}