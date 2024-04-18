#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "commands.h"
#include "paths.h"

static FILE *input_stream = NULL;
extern char DEFAULT_PATH;

static void cleanup()
{
    // free all search Paths
    freePaths();

    // close if a file is opened
    if (input_stream != NULL && input_stream != stdin)
    {
        fclose(input_stream);
    }

}

static void process(FILE *input_stream)
{
    char *buffer = NULL;
    size_t len = 0;

    while (1)
    {
        if(input_stream == stdin)
            fprintf(stdout, "./wish> ");
        
        if(getline(&buffer, &len, input_stream) == -1){
            break;
        }

        if (strcmp(buffer, "exit\n") == 0)
        {
            break;
        }
        
        char *dup = strdup(buffer);
        setCommand(dup);
        free(dup);
    }

    free(buffer);
}

int main(int argc, char *argv[])
{
    atexit(cleanup);

    input_stream = stdin;
    // default path is /bin/
    setSearchPath(&DEFAULT_PATH);

    if (argc == 2)
    {
        input_stream = fopen(argv[1], "r");

        if (input_stream == NULL)
        {
            fprintf(stderr, "An error has occurred\n");
            exit(EXIT_FAILURE);
        }
    }
    else if (argc > 2)
    {
        fprintf(stderr, "An error has occurred\n");
        exit(EXIT_FAILURE);
    }

    process(input_stream);

    return EXIT_SUCCESS;
}
