#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "utils.h"

void printPaths(char **path, int num_path){
    int i = 0;
    for (; i < num_path; i++)
    {
        printf("path #%d : %s\n", i, path[i]);
    }
}

char* firstNonWhitespace(const char *str){
    while(*str && isspace(*str)){
        str++;
    }

    return (char*)str;
}

void trimWhiteSpaceAtEnd(char *str){
    int length = strlen(str);
    int i = length - 1;

    while(i >= 0 && isspace(str[i])){
        str[i] = '\0';
        i--;
    }
}

void trimNewline(char *str)
{
    if(str != NULL){
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n')
        {
            str[len - 1] = '\0';
        }
    }
}

void addSlashIfNeeded(char** strr) {
    char *str = *strr;
    size_t len = strlen(str);
    
    // Check if the last character is a slash
    if (len > 0 && str[len - 1] != '/') {
        // Allocate memory for the new string with an additional character for the slash
        char *new_str = (char*) realloc((void*)str, (len + 2) * sizeof(char));
        if (new_str == NULL) {
            fprintf(stderr, "Memory reallocation failed.\n");
        }

        // Update the original pointer to point to the newly allocated memory
        *strr = new_str;

        // Append a slash to the end of the string
        new_str[len] = '/';
        new_str[len + 1] = '\0'; // Ensure proper null-termination

    }
}