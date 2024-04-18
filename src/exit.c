#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"

void commandExit(char *input){
    // raise an error exit w/ args
    char *arg = strsep(&input, " ");
    if(arg != NULL){
        fprintf(stderr, "An error has occurred\n");
    }else{
        exit(EXIT_SUCCESS);
    }
}