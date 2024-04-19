#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "parallel.h"
#include "utils.h"
#include "custom.h"
#include "commands.h"

extern int async;

int checkIfParallel(const char* input){
    char *ampersand = strpbrk(input, "&");
    if(ampersand != NULL){
        return 1;
    }

    return 0;
}

void setParallel(char *input){
    char *command = NULL;
    command = strtok(input, "&\n");
    async = 1;

    while (command != NULL) {

        // printf("command: %d\n",command);
        char *command_no_ws = firstNonWhitespace(command);
        // printf("command_no_ws: %d\n",command_no_ws);
        //trimWhiteSpaceAtEnd(command_no_ws);
        // printf("command_no_ws:%d\n", command_no_ws);
        // printf("command_no_ws:%s\n", command_no_ws);
        // printf("len(command_no_ws):%d\n", strlen(command_no_ws));

        int length = strlen(command_no_ws);
        int i = length - 1;

        while(i >= 0 && isspace(command_no_ws[i])){
            command_no_ws[i] = '\0';
            i--;
        }

        char *dup = strdup(command_no_ws);
        setCommand(dup);
        free(dup);

        command = strtok(NULL, "&\n");
    }

    async = 0;
}