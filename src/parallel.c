#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parallel.h"
#include "utils.h"
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
    char *parallel_cmds = firstNonWhitespace(input);
    trimWhiteSpaceAtEnd(parallel_cmds);

    // Find the last occurrence of '&'
    char *last_ampersand = strrchr(parallel_cmds, '&'); 
    
    sync_flag = 0;

    char *token = NULL;
    token = strtok(parallel_cmds, "&\n");

    while (token != NULL) {
        trimWhiteSpaceAtEnd(token);
        token = firstNonWhitespace(token);

        if(last_ampersand == token + strlen(token)){
            sync_flag = 1;
        }
        
        char *dup = strdup(token);
        setCommand(dup);
        free(dup);

        token = strtok(NULL, "&\n");
    }

}