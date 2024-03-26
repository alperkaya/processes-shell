#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#include "utils.h"
#include "paths.h"

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
        execv(cmd_args[0], cmd_args);
        _exit(0);
    }
    else
    {
        wait(NULL);

        // cleanup cmd and arguments
        int i = 0;
        for (; i < 10; i++)
        {
            free(cmd_args[i]);
        }
    }
}

static void runCustomCommand(char *input, char *cmd){
    // we have cmd here
    // before executing this cmd,
    // we have to check if it is valid by access
    char *cmd_args[10] = {NULL};
    if (appendPath(cmd, &cmd_args[0]) == 0)
    {
        // parse other args which will go in as input args to cmd
        // decide delimeter? until newline char or &
        char *arg = NULL;
        int num_args = 1;

        while ((arg = strsep(&input, " ")) != NULL)
        {
            if (strcmp(arg, "\n") == 0 || strcmp(arg, "&") == 0)
                break;
            trimNewline(arg);
            if (cmd_args == NULL)
            {
                fprintf(stderr, "An error has occurred\n");
                exit(EXIT_FAILURE);
            }
            cmd_args[num_args] = strdup(arg);

            num_args++;
        }
        // execute the command
        forkCommand(cmd_args);
    }
}

void setCommand(char *input)
{
    char *cmd = strsep(&input, " ");
    trimNewline(cmd);

    if (cmd != NULL)
    {
        if (strcmp(cmd, "path") == 0)
        {
            setSearchPath(input);
            printPaths(path, num_path);
        }
        else if (strcmp(cmd, "exit") == 0)
        {
            exit(EXIT_SUCCESS);
        }
        else if (strcmp(cmd, "cd") == 0)
        {
            // TODO
            // cd takes only one argument
            // args = 0 or > 1 is an erro
            // use chdir to change dir
        }
        else
        {
            runCustomCommand(input, cmd);
        }
    }
    else
    {
        fprintf(stderr, "An error has occurred\n");
    }
}