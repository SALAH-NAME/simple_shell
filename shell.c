#include "shell.h"

/**
 * main - Entry point
 * @argc: num of args
 * @argv: array of args
 *
 * Return: Always 0
 */


int main(void)
{
	char *line;
	char *argv[2];
	int status, _run = 1;
	size_t len = 0;

	while (_run)
	{
		printf("$ ");
		line = NULL;

		if (getline(&line, &len, stdin) == -1)
			break;

		line[strcspn(line, "\n")] = 0; /* remove newline character */
		argv[0] = line;
		argv[1] = NULL;

		if (fork() == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
				perror(argv[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}

	return (EXIT_SUCCESS);
}
