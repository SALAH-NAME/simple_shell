#include "shell.h"

/**
 * main - Entry point
 * @argc: num of args
 * @argv: array of args
 *
 * Return: Always 0
 */

int main(int __attribute__((unused)) argc, char **argv)
{
	char *line;
	char *args[2];
	int status, _run = 1;
	size_t len = 0;

	while (_run)
	{
		printf("#cisfun$ ");
		line = NULL;

		if (getline(&line, &len, stdin) == -1)
			break;

		line[strcspn(line, "\n")] = 0; /* remove newline character */
		args[0] = line;
		args[1] = NULL;

		if (fork() == 0)
		{
			if (execve(args[0], args, NULL) == -1)
				printf("%s: No such file or directory\n", argv[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}

	return (EXIT_SUCCESS);
}
