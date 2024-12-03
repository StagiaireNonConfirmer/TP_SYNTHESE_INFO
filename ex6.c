#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_COMMAND_LENGTH 1024
#define PROMPT "enseash [exit:%d|%ldms] %% "

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
        struct timespec start, end;
        
        pid_t pid = fork();
        waitpid(pid, &status, 0);
        clock_gettime(CLOCK_MONOTONIC, &start);

        char prompt[MAX_COMMAND_LENGTH];
        write(STDOUT_FILENO, prompt, strlen(prompt));

        fgets(command, MAX_COMMAND_LENGTH, stdin);
        command[strcspn(command, "\n")] = 0;

        if ((strcmp(command, "exit") == 0) || feof(stdin)) {
			// Display exit message and calculate execution time
            write(STDOUT_FILENO, exit_bye, strlen(exit_bye));
            waitpid(pid, &status, 0);
            clock_gettime(CLOCK_MONOTONIC, &end);
            long exec_time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
            exec_time = exec_time / 100;
			char prompt[MAX_COMMAND_LENGTH];
            sprintf(prompt, PROMPT, WEXITSTATUS(status), exec_time);
             write(STDOUT_FILENO, prompt, strlen(prompt));
            break;
        } else if (strcmp(command, "fortune") == 0) {
			// Execute fortune command in child process
            if (pid == 0) {
                execvp(fortune_args[0], fortune_args);                 
                waitpid(pid, &status, 0);
				clock_gettime(CLOCK_MONOTONIC, &end);
				long exec_time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
				char prompt[MAX_COMMAND_LENGTH];
				sprintf(prompt, PROMPT, WEXITSTATUS(status), exec_time);
				write(STDOUT_FILENO, prompt, strlen(prompt));
            }
        } else if((strcmp(command, command) == 0)) {
			// Parse and execute commands with input/output redirection
			char *commnd_pr[10];
            char *token;
            int i = 0;

            token = strtok(command, " ");
            while (token != NULL && i < 9) {
                    commnd_pr[i] = token;
                    i++;
					token = strtok(NULL, " ");
            }
            commnd_pr[i] = NULL;

            // Wait for child process, calculate execution time, and display prompt
            waitpid(pid, &status, 0); // Wait for the child process to finish
            clock_gettime(CLOCK_MONOTONIC, &end);
            long exec_time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
            exec_time = exec_time / 100;
            char prompt[MAX_COMMAND_LENGTH];
            sprintf(prompt, PROMPT, WEXITSTATUS(status), exec_time); // Display prompt with exit status and execution time
            write(STDOUT_FILENO, prompt, strlen(prompt));

            // Execute the parsed command in the child process
            execvp(commnd_pr[0], commnd_pr);
        } else {
            // Display error message and prompt
            write(STDOUT_FILENO, error_message, strlen(error_message));
            waitpid(pid, &status, 0);
            clock_gettime(CLOCK_MONOTONIC, &end);
            long exec_time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000;
            exec_time = exec_time / 100;
            char prompt[MAX_COMMAND_LENGTH];
            sprintf(prompt, PROMPT, WEXITSTATUS(status), exec_time);
            write(STDOUT_FILENO, prompt, strlen(prompt));
        }
    }
    return 0;
}
