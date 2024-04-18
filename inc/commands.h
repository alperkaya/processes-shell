#ifndef COMMANDS_H
#define COMMANDS_H

// Define a function pointer type for the strategy
typedef void (*Command)(char*);

// Define command functions
void commandExit(char *input);
void commandCd(char *input);
void commandPath(char *input);
void commandCustom(char *input);

void setCommand(char *input);

#endif // COMMANDS_H