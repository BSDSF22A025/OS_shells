#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define MAX_COMMAND_LEN 1024

void handle_sigchld(int sig) {
    // Wait for any child process to prevent zombie processes
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void execute_command(char *command) {
    char *args[MAX_COMMAND_LEN / 2 + 1];
    int background = 0;
    int i = 0;

    // Parse the command into arguments
    args[i] = strtok(command, " \t\n");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " \t\n");
    }

    // Check if the command should run in the background
    if (i > 0 && strcmp(args[i - 1], "&") == 0) {
        background = 1;
        args[i - 1] = NULL; // Remove '&' from arguments
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
    } else if (pid == 0) {
        // Child process
        execvp(args[0], args);
        perror("Command execution failed");
        exit(1);
    } else {
        // Parent process
        if (!background) {
            // Wait for the child process if it's not a background task
            waitpid(pid, NULL, 0);
        } else {
            printf("[1] %d\n", pid);  // Display background process ID
        }
    }
}

int main() {
    char command[MAX_COMMAND_LEN];

    // Set up SIGCHLD handler to clean up zombie processes
    signal(SIGCHLD, handle_sigchld);

    while (1) {
        printf("Lubaba's shell@:- "); // Display shell prompt
        fflush(stdout);

        // Read command input
        if (fgets(command, MAX_COMMAND_LEN, stdin) == NULL) {
            // Exit if EOF (Ctrl+D)
            printf("\n");
            break;
        }

        // Execute the command
        execute_command(command);
    }

    return 0;
}

