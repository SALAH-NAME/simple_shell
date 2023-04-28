#include "shell.h"

/**
 * split_line - Split a command line into separate arguments
 * @line: The command line to split
 * @nargs: Pointer to an integer where the number of arguments will be stored
 *
 * Return: An array of strings containing the arguments
 */
char **split_line(char *line, int *nargs)
{
	char **args;
	char *arg;
	int i;

	args = malloc(MAX_ARGS * sizeof(char *));
	arg = strtok(line, " \t\n\r");
	i = 0;
	while (arg != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = arg;
		arg = strtok(NULL, " \t\n\r");
	}
	args[i] = NULL;
	*nargs = i;

	return (args);
}

/**
 * main - Simple UNIX command line interpreter
 * @argc: num of args
 * @argv: array of args
 *
 * Return: 0 on success, 1 on error
 */
int main(int __attribute__((unused))argc, char __attribute__((unused))**argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	int nargs;
	int status;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			printf("($) ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;
		args = split_line(line, &nargs);
		if (nargs > 0)
		{
			if (fork() == 0)
			{
				execve(args[0], args, NULL);
				perror(args[0]);
				exit(1);
			}
			else
			wait(&status);
		}
		free(args);
	}
	free(line);
	return (0);
}
