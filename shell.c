#include "shell.h"

/**
 * main - the main function of a simiple shell
 * @argc: num of agrs
 * @argv: array of args
 *
 * Return: always 0
 */

int main(int __attribute__((unused))argc, char __attribute__((unused))**argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *args[2];
	int status;
	int interactive = isatty(STDIN_FILENO);

	while (1)
	{
		if (interactive)
			printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;
		line[strcspn(line, "\n")] = '\0';
		args[0] = line;
		args[1] = NULL;
		if (fork() == 0)
		{
			execve(args[0], args, NULL);
			perror(args[0]);
			exit(1);
		}
		else
		wait(&status);
		}
	free(line);

	return (0);
}
