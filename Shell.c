#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LENGTH 100
#define MAX_COUNT 10

void get_history(char *history[], int history_count) {
    printf("Command history:\n");
    for (int i = 0; i < history_count; i++) {
        printf("%d. %s\n", i + 1, history[i]);
    }
}

void add_history(char *history[], int *history_count, char *command) {
    if (*history_count < MAX_COUNT) {
        history[*history_count] = strdup(command);
        (*history_count)++;
    } else {
        free(history[0]);
        for (int i = 1; i < MAX_COUNT; i++) {
            history[i - 1] = history[i];
        }
        history[MAX_COUNT - 1] = strdup(command);
    }
}

void execute_command(char *command, char *history[], int *history_count) {
    if (strcmp(command, "exit") == 0) {
        exit(0);
    } else if (strcmp(command, "history") == 0) {
        get_history(history, *history_count);
    } else if (strcmp(command, "!!") == 0) {
        if (*history_count == 0) {
            printf("No commands yet.\n");
            return;
        }
        execute_command(history[*history_count - 1], history, history_count);
    } else if (command[0] == '!') {
        int index = atoi(command + 1);
        if (index < 1 && index > *history_count) {
            printf("Invalid Index.\n");
            return;
        } else if (history[index - 1] == NULL) {
            printf("No command in History.\n");
            return;
        }
        execute_command(history[index - 1], history, history_count);
    } else if (strcmp(command, "jobs") == 0) {
        system("ps");        
    } else {
        add_history(history, history_count, command);
        int background = 0;
        if (command[strlen(command) - 1] == '&') {
            background = 1;
            command[strlen(command) - 1] = '\0';
        }
        pid_t pid = fork();
        if (pid == 0) {
            char *args[MAX_LENGTH / 2 + 1];
            char *token = strtok(command, " ");
            int i = 0;
            while (token != NULL) {
                args[i] = token;
                token = strtok(NULL, " ");
                i++;
            }
            args[i] = NULL;
            execvp(args[0], args);
            printf("Error: Invalid Command!!\n");
            exit(1);
        } else {
            if (!background) {
                int status;
                waitpid(pid, &status, 0);
            }
        }
    }
}

int main() {
    char *history[MAX_COUNT];
    for (int i = 0; i < MAX_COUNT; i++) {
        history[i] = NULL;
    }
    int history_count = 0;
    while (1) {
        char command[MAX_LENGTH];
        printf("Shell> ");
        fgets(command, MAX_LENGTH, stdin);
        if (command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }
        if (strlen(command) == 0) {
            continue;
        }
        execute_command(command, history, &history_count);
    }
    return 0;
}