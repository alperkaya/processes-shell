#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#include "commands.h"

void commandCd(char *input){
    // cd takes only one argument
    // args = 0 or > 1 is an erro
    // use chdir to change dir
    char *arg = strsep(&input, " \n");

    if(arg == NULL || strcmp(input, "") != 0){
        fprintf(stderr, "An error has occurred\n");
    }else{
        int r = chdir(arg);

        if(r == -1){
            fprintf(stderr, "An error has occurred\n");
        }
    }
}