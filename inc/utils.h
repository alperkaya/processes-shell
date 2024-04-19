#ifndef UTILS_H
#define UTILS_H

extern void printPaths(char **path, int num_path);
extern void trimNewline(char *str);
extern void addSlashToEnd(char **str);
extern int slashExistAtEnd(char *str);
extern char* firstNonWhitespace(const char *str);
extern void trimWhiteSpaceAtEnd(char *str);
#endif // UTILS_H

