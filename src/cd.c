#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#include "commands.h"

void commandCd(char *input){
    // cd takes only one argument
    char *arg = strsep(&input, " \n");

    // args = 0 or > 1 is an erro
    if(arg == NULL || (input != NULL && strlen(input)) > 0){
        fprintf(stderr, "An error has occurred\n");
    }else{
        // use chdir to change dir
        int r = chdir(arg);

        if(r == -1){
            fprintf(stderr, "An error has occurred\n");
        }
    }
}