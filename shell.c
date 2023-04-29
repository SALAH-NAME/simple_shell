#include "shell.h"

/**
 * main - the main function of the shell
 * @argc: num of args
 * @argv: array of args
 *
 * Return: 0 on success
 */
int main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	int nargs;
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
			execute_command(args, argv[0]);
		free(args);
	}
	free(line);
	return (0);
}
