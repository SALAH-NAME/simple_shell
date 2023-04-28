#ifndef __SHELL__HEAD__
#define __SHELL__HEAD__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 128

char **split_line(char *line, int *nargs);

#endif
