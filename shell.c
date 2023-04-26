#include "shell.h"

/**
 * print_prompt - prints prompt
 *
 * Return: void
 */

void print_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * read_input - reads input from user
 * @line: pointer to line buffer
 * @len: pointer to line length
 *
 * Return: number of characters read
 */

ssize_t read_input(char **line, size_t *len)
{
	ssize_t nread;

	nread = getline(line, len, stdin);
	if (nread == -1)
	{
		exit(EXIT_SUCCESS);
	}
	(*line)[nread - 1] = '\0';

	return (nread);
}

/**
 * execute_command - executes command
 * @argv: pointer to argument vector
 * @args: pointer to argument string
 *
 * Return: void
 */

void execute_command(char **argv, char **args)
{
	int status;
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			printf("%s: No such file or directory\n", args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - entry point
 * @argc: number of arguments passed to program
 * @args: array of pointers to argument strings
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */

int main(int __attribute__((unused))argc, char __attribute__((unused))**args)
{
	char *line = NULL;
	size_t len = 0;
	char *argv[2];
	ssize_t nread;

	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			print_prompt();
			nread = read_input(&line, &len);
			if (nread == 0)
			{
				break;
			}
		argv[0] = line;
		argv[1] = NULL;
		execute_command(argv, args);
		}
	}
	else
	{
		nread = read_input(&line, &len);
		if (nread != 0)
		{
			argv[0] = line;
			argv[1] = NULL;
			execute_command(argv, args);
		}
	}

	return (EXIT_SUCCESS);
}
