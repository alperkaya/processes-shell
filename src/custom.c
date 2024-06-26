#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#include "utils.h"
#include "paths.h"
#include "commands.h"
#include "custom.h"

#define MAX_ARG 48
static char *cmd_args[MAX_ARG] = {NULL};
static int num_args = 0;
extern char custom_cmd[];
static FILE *user_stdout = NULL;
int sync_flag = 1;
static char *out_stream = NULL;

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
        user_stdout = fopen(out_stream, "w");
        // printf("child process: %s\n", out_stream);
        free(out_stream);

        if(user_stdout != NULL){
            if(dup2(fileno(user_stdout), STDOUT_FILENO) == -1){
                fprintf(stderr, "An error has occurred\n");
                exit(EXIT_FAILURE);
            }

        }

        if(execv(cmd_args[0], (cmd_args+1)) == -1){
            fprintf(stderr, "An error has occurred3\n");
        }

        if(user_stdout != NULL){
            //fclose(user_stdout);
        }

        _exit(0);
    }
    else
    {
        // This is the parent process
        // printf("sync_flag:%d\n", sync_flag);
        // wait for the child to finish
        if(sync_flag == 1){
            while (wait(NULL) > 0);
            // wait(NULL);
        }
        
    }
}

int tokenizeByGreaterThan(char *str) {
    int count = 0;
    
    // Count the occurrences of '>'
    int i = 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] == '>')
            count++;
    }
    
    // If there are more than one '>', return failure
    if (count > 1){
        fprintf(stderr, "An error has occurred\n");
        return -1;
    }


    if(str != NULL){
        // printf("str %s\n", str);
        out_stream = strdup(str);
        //printf("out_stream:%s\n", out_stream);

        if(out_stream == NULL)
        {
            fprintf(stderr, "An error has occurred\n");
            return -1;
        }

    }


    return 0; // Success
}

int setRedirection(char *arg, char *input){
    int result = 0;

    //printf("setArguments-output:%s\n", input);

    // fail if no input, after >
    // fail if multiple files given
    if(input == NULL || strpbrk(input, " ") != NULL){
        fprintf(stderr, "An error has occurred\n");
        return -1;
    }

    input = firstNonWhitespace(input);
    char *redirect = strdup(input);
    
    if(redirect != NULL){
        // this is weird
        // if i use input, the output file ends with ?
        redirect[strlen(redirect)] = '\0';
        result = tokenizeByGreaterThan(redirect);
        free(redirect);
    }else{
        fprintf(stderr, "An error has occurred\n");
        result = -1;
    }

    

    return result;
}

static int setArgsAndRedirection(char *input){
    char *arg = NULL;
    int result = 0;
    while ((arg = strsep(&input, " ")) != NULL && num_args < MAX_ARG)
    {           
        if(num_args == MAX_ARG){
            fprintf(stderr, "An error has occurred\n");
            return -1;
        }
        
        trimNewline(arg);
        

        // > is in between whitespaces
        if(*arg == '>'){
            result = setRedirection(arg, input);
            break;
        }else{
            
            char *token = strsep(&arg, ">");

            if(arg != NULL){
                tokenizeByGreaterThan(arg);
            }

            cmd_args[num_args++] = strdup(token);
        }
        
    }

    return result;
}


static void resetArgs(){
    // cleanup cmd and arguments
    int i = 0;
    for (; i < num_args; i++)
    {
        if(cmd_args[i] != NULL){
            free(cmd_args[i]);
        }
    }

    if(out_stream != NULL){
        free(out_stream);
        out_stream = NULL;
    }

    num_args = 0;
    sync_flag = 1;
}

void commandCustom(char *input){

    int result = 0;

    // the first arg is the command with path
    if (appendPath(custom_cmd, &cmd_args[num_args]) == 0)
    {   
        num_args++;
        // the second arg is the command itself
        cmd_args[num_args++] = strdup(custom_cmd);

        if(result == 0){
            result = setArgsAndRedirection(input);
        }

        // execute fork
        if(result == 0){
            forkCommand(cmd_args);
        }

        resetArgs();
    }

}



