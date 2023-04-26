#include "shell.h"

/**
 * print_prompt - Prints the prompt "#cisfun$ " to the console.
 */

void print_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * read_input - Reads input from the console and stores it in a buffer.
 * @line: Pointer to the buffer.
 * @len: Length of the buffer.
 *
 * Return: Number of bytes read.
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
 * execute_command - Executes the command stored in the buffer.
 * @argv: Array of pointers containing the command and its arguments.
 * @args: Array of pointers containing the program name and its arguments.
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
 * main - Entry point. Runs an infinite loop that prints a prompt,
 * reads input from the console, and executes the command stored in
 * the buffer.
 * @argc: Number of command-line arguments.
 * @args: Array of pointers to strings containing the command-line arguments.
 *
 * Return: Always 0.
 */

int main(int __attribute__((unused))argc, char __attribute__((unused))**args)
{
	char *line = NULL;
	size_t len = 0;
	char *argv[2];
	ssize_t nread;

	if (isatty(fileno(stdin)))
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
