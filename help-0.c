#include "shell.h"

/**
 * execute_command_in_path - search for a command in the PATH and execute it
 * @args: the command and its arguments
 *
 * Return: void
 */
void execute_command_in_path(char **args)
{
	char *path = getenv("PATH");
	char *dir = strtok(path, ":");

	while (dir != NULL)
	{
		char command_path[MAX_LINE];

		snprintf(command_path, MAX_LINE, "%s/%s", dir, args[0]);
		if (execve(command_path, args, NULL) != -1)
			return;
		dir = strtok(NULL, ":");
	}
}

/**
 * exit_shell - exit the shell
 * @args: the command and its arguments
 *
 * Return: void
 */
void exit_shell(char **args)
{
	int exit_status = 0;

	if (args[1] != NULL)
		exit_status = atoi(args[1]);
	free(args);
	exit(exit_status);
}

/**
 * execute_command - execute a command
 * @args: the command and its arguments
 * @argv: the arguments passed to main
 *
 * Return: void
 */
void execute_command(char **args, char *argv)
{
	static int command_number;
	pid_t pid;
	int status;

	command_number = 0;
	if (strcmp(args[0], "exit") == 0)
		exit_shell(args);

	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Fork failed\n");
		exit(1);
	}
	else if (pid == 0)
	{
		char *envp[] = {NULL};

		if (execve(args[0], args, envp) == -1)
			execute_command_in_path(args);
		if (isatty(STDIN_FILENO))
			fprintf(stderr, "%s: command not found\n", args[0]);
		else
			fprintf(stderr, "%s: %d: %s: not found\n", argv,
					++command_number, args[0]);
		free(args);
		exit(127);
	}
	else
		waitpid(pid, &status, 0);
}

/**
 * split_line - split a line into an array of arguments
 * @line: the line to split
 * @nargs: a pointer to an integer where the number of arguments will be stored
 *
 * Return: an array of arguments
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
