#include <stdio.h>
#include <string.h>
#include "utils.h"

void printPaths(char **path, int num_path){
    int i = 0;
    for (; i < num_path; i++)
    {
        printf("path #%d : %s\n", i, path[i]);
    }
}

void trimNewline(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
    {
        str[len - 1] = '\0';
    }
}