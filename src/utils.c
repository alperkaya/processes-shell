#include <stdio.h>
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

void clearWhiteSpaceAtEnd(char *str){
    int length = strlen(str);
    int i = length - 2;

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

int slashExistAtEnd(char *str){
    if(str[strlen(str) - 1] == '/'){
        return 1;
    }

    return 0;
}

void addSlashToEnd(char **str){
    // add / at the end if user didnt provide
    char *destination = *str;
    // Step 2: Calculate the length of the copied string
    size_t length = strlen(*str);
    // Step 3: Append the character at the end
    destination[length] = '/';        
    // Step 4: Null-terminate the string
    destination[length + 1] = '\0';
}