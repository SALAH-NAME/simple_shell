#ifndef __SHELL__HEAD__
#define __SHELL__HEAD__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 128
#define MAX_LINE 1024

void execute_command_in_path(char **args);
void exit_shell(char **args);
void execute_command(char **args, char *argv);
char **split_line(char *line, int *nargs);
char *_strtok(char *str, const char *delim);

#endif
