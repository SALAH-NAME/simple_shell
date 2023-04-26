#ifndef __SHELL__HEAD__
#define __SHELL__HEAD__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void print_prompt(void);
ssize_t read_input(char **line, size_t *len);
void execute_command(char **argv, char **args);

#endif
