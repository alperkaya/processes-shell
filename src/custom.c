#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#include "utils.h"
#include "paths.h"
#include "commands.h"

#define MAX_ARG 48
static char *cmd_args[MAX_ARG] = {NULL};
static int num_args = 0;
extern char custom_cmd[];
static FILE *user_stdout = NULL;

//static char redirection_file[255] = {0};


static void forkCommand(char **cmd_args)
{
    int rc = fork();
    if (rc < 0)
    {
        fprintf(stderr, "An error has occurred\n");
        exit(EXIT_FAILURE);
    }
    else if (rc == 0)
    {
        // This is the child process
        if(user_stdout != NULL){
            if(dup2(fileno(user_stdout), STDOUT_FILENO) == -1){
                fprintf(stderr, "An error has occurred\n");
                exit(EXIT_FAILURE);
            }

            fclose(user_stdout);
        }

        if(execv(cmd_args[0], (cmd_args+1)) == -1){
            fprintf(stderr, "An error has occurred3\n");
        }
        _exit(0);
    }
    else
    {
        // This is the parent process

        // wait for the child to finish
        wait(NULL);

        // cleanup cmd and arguments
        int i = 0;
        for (; i < num_args; i++)
        {
            free(cmd_args[i]);
        }

        num_args = 0;
        user_stdout = NULL;
    }
}

// static int setRedirection(char *input){
//     const char redirection = '>';
//     char *redirect_char = strpbrk(input, &redirection);

//     if(redirect_char != NULL){
//         char *input_after_redirect = redirect_char + 1;
//         if (*input_after_redirect == '\0' || *input_after_redirect == '\n') {
//             fprintf(stderr, "An error has occurred\n");
//             return -1;
//         }

//         char *args = strsep(&input, " ");
//         trimNewline(args);

//         // redirection found
//         return 1;
//     }

//     // no redirection
//     return 0;
// }

static int setArguments(char *input){
    char *arg = NULL;
    //int num_args = 2;

    while ((arg = strsep(&input, " ")) != NULL && num_args < MAX_ARG)
    {
        if(num_args == MAX_ARG){
            fprintf(stderr, "An error has occurred\n");
            return -1;
        }
        
        trimNewline(arg);
        
        // check for redirection
        const char redirection = '>';
        char *redirect_char = strpbrk(arg, &redirection);
        if(redirect_char != NULL){
            char *input_after_redirect = redirect_char + 1;
            if (*input_after_redirect == '\0' || *input_after_redirect == '\n') {
                fprintf(stderr, "An error has occurred\n");
                return -1;
            }

            // check if there is argument before >
            if(redirect_char > arg){
                
                // get size
                // allocate memory
                char *argument = malloc((redirect_char-arg) * sizeof(char));
                strncpy(argument, arg, redirect_char-arg);
                //printf("arg: %s\n", argument);

                cmd_args[num_args] = strdup(argument);
                num_args++;
            }

            // check if substring contains another >
            // then fail
            char *redirect_char = strpbrk(input_after_redirect, &redirection);
            if(redirect_char != NULL){
                fprintf(stderr, "An error has occurred\n");
                return -1;
            }

            // get substring after > char
            // set output stream to substring
            char *out_stream = malloc(strlen(input_after_redirect) + 1);
            strcpy(out_stream, input_after_redirect);
            out_stream[strlen(input_after_redirect)] = '\0';
            user_stdout = fopen(out_stream, "w");

        }else{
            cmd_args[num_args++] = strdup(arg);
        }

    }

    return 0;
}

void commandCustom(char *input){

    int result = 0;

    // the first arg is the command with path
    if (appendPath(custom_cmd, &cmd_args[num_args++]) == 0)
    {
        // the second arg is the command itself
        cmd_args[num_args++] = strdup(custom_cmd);

        //result = setRedirection(input);

        if(result == 0){
            result = setArguments(input);
        }

        // execute fork
        if(result == 0){
            forkCommand(cmd_args);
        }
    }

}




