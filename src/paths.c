#include <stdlib.h>
#include <stdio.h>
#include <string.h> //stcmp
#include <unistd.h> 

#include "utils.h"
#include "commands.h"

char **path = NULL;
int num_path = 0;
char DEFAULT_PATH[6] = "/bin/";


// PATH
// if a command cant found in search paths, throw an error
//
// user will enter a list of string for search paths dynamically
// if no input is given, no search path is available,
//              only built-in cmds works
// data structure
// I will keep an array of char pointers, for each pointer
//              assign enough memory for the string
//

void freePaths()
{
    while (num_path > 0)
    {
        free(path[num_path - 1]);
        num_path--;
    }
}

void commandPath(char *path_list)
{
    char *arg = NULL;

    freePaths();

    while ((arg = strsep(&path_list, " ")) != NULL)
    //while ((arg = stringSep(&path_list, " ")) != NULL)
    {
        trimNewline(arg);
        
        // increase num of path
        path = (char **) realloc(path, (num_path + 1) * sizeof(char *));

        path[num_path] = strdup(arg);
        addSlashIfNeeded(&path[num_path]);

        num_path++;
    }
}

// BUILT-IN CMD
// check if the cmd is built-in
// yes -> invoke the implementation within this source code
//
// cd -> use chdir() system call w/ arg supplied by user
//      if chdir fails, throw an error
//      if arg==0 or arg>1 throw an error
//
// exit -> exit(0);
//
// path -> 0 or more arguments
// ./wish> path /bin /usr/bin
// add arguments to search path
// if no argument given, run only built in cmds
// path overwrites the old path with the new one
//
//

int appendPath(char *cmd, char **exec_cmd)
{
    // we have to search through search path list
    int i = 0;
    for (; i < num_path; i++)
    {
        char cmd_full_path[255];
        sprintf(cmd_full_path, "%s%s", path[i], cmd);
        if (access(cmd_full_path, X_OK) == 0)
        {
            // append path to cmd
            // str1 = path
            // str2 = cmd
            // str2 = path+cmd
            // return str2
            if ((*exec_cmd = strdup(cmd_full_path)) != NULL)
            {
                //printf("path: %s,%d\n", *exec_cmd, i);  
                return 0;
            }
        }
    }

    fprintf(stderr, "An error has occurred\n");

    return -1;
}
