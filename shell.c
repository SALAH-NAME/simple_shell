#include "shell.h"

/**
 * main - Entry point
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
				printf("./shell: No such file or directory\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
		}
	}

	return (EXIT_SUCCESS);
}
