#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define PROMPT "enseash [exit:%d] %% "

int main() {
    int status;
    char command[MAX_COMMAND_LENGTH];
    char welcome_message[] = "Bienvenue dans le Shell ENSEA.\n";
    char exit_message[] = "Pour quitter, tapez 'exit'.\n";
    char exit_bye[] = "Bye bye...'.\n";
    char error_message[] = "error_message \n";
    char *fortune_args[] = {"fortune", NULL};

    // Display welcome and exit messages
    write(STDOUT_FILENO, welcome_message, strlen(welcome_message));
    write(STDOUT_FILENO, exit_message, strlen(exit_message));
    
    while (1) {
        
        pid_t pid = fork();
        waitpid(pid, &status, 0);

        char prompt[MAX_COMMAND_LENGTH];
        write(STDOUT_FILENO, prompt, strlen(prompt));

        fgets(command, MAX_COMMAND_LENGTH, stdin);
        command[strcspn(command, "\n")] = 0;

        if ((strcmp(command, "exit") == 0) || feof(stdin)) {
			// Display exit message
            write(STDOUT_FILENO, exit_bye, strlen(exit_bye));
            waitpid(pid, &status, 0);
			char prompt[MAX_COMMAND_LENGTH];
            sprintf(prompt, PROMPT, WEXITSTATUS(status));
             write(STDOUT_FILENO, prompt, strlen(prompt));
            break;
        } else if (strcmp(command, "fortune") == 0) {
			// Execute fortune command in child process
            if (pid == 0) {
                execvp(fortune_args[0], fortune_args);                 
                waitpid(pid, &status, 0);
				char prompt[MAX_COMMAND_LENGTH];
				sprintf(prompt, PROMPT, WEXITSTATUS(status));
				write(STDOUT_FILENO, prompt, strlen(prompt));
            }
        } else {
            // Display error message and prompt
            write(STDOUT_FILENO, error_message, strlen(error_message));
            waitpid(pid, &status, 0);
            char prompt[MAX_COMMAND_LENGTH];
            sprintf(prompt, PROMPT, WEXITSTATUS(status));
            write(STDOUT_FILENO, prompt, strlen(prompt));
        }
    }
    return 0;
}
