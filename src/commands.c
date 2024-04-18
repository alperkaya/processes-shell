#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

#include "utils.h"
#include "commands.h"

char custom_cmd[255];

void setCommand(char *input)
{
    char *cmd = strsep(&input, " ");
    trimNewline(cmd);
    
    Command selectedCommand = NULL;

    if (cmd != NULL)
    {
        if (strcmp(cmd, "path") == 0)
        {
            selectedCommand = commandPath;
        }
        else if (strcmp(cmd, "exit") == 0)
        {
            selectedCommand = commandExit;
        }
        else if (strcmp(cmd, "cd") == 0)
        {
            selectedCommand = commandCd;
        }
        else
        {
            strcpy(custom_cmd, cmd);
            selectedCommand = commandCustom;
        }

        // Execute selected command
        selectedCommand(input);
    }
    else
    {
        fprintf(stderr, "An error has occurred\n");
    }
}