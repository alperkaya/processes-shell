#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parallel.h"
#include "utils.h"
#include "custom.h"
#include "commands.h"

extern int sync_flag;

int checkIfParallel(const char* input){
    char *ampersand = strpbrk(input, "&");
    if(ampersand != NULL){
        return 1;
    }

    return 0;
}

void setParallel(char *input) {
    char *command = NULL;
    char *command_no_ws = firstNonWhitespace(input);
    trimWhiteSpaceAtEnd(command_no_ws);

    // TODO refactor code duplication
    int length = strlen(input);
    int i = length - 1;

    while (i >= 0 && isspace(command_no_ws[i])) {
        command_no_ws[i] = '\0';
        i--;
    }

    char *last_ampersand = strrchr(input, '&'); // Find the last occurrence of '&'

    sync_flag = 0;

    command = strtok(input, "&\n");

    while (command != NULL) {
        // printf("command: %d, len:%d\n", command, strlen(command));
        // printf("last_ampersand: %d\n", last_ampersand);
        if(last_ampersand == command + strlen(command)){
            sync_flag = 1;
        }

        char *command_no_ws = firstNonWhitespace(command);

        int length = strlen(command_no_ws);
        int i = length - 1;

        while (i >= 0 && isspace(command_no_ws[i])) {
            command_no_ws[i] = '\0';
            i--;
        }
        
        
        char *dup = strdup(command_no_ws);
        setCommand(dup);
        free(dup);

        command = strtok(NULL, "&\n");
    }

}