#ifndef PATHS_H
#define PATHS_H

extern char **path;
extern int num_path;

void freePaths();
void setSearchPath(char *path_list);
int appendPath(char *cmd, char **exec_cmd);

#endif // PATHS_H

