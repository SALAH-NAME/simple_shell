#include "shell.h"
/**
* _strtok - breaks a string into a sequence of zero or more nonempty tokens
* @str: the string to be tokenized
* @delim: the delimiter character
*
* Return: a pointer to the next token, or NULL if there are no more tokens
*/
char *_strtok(char *str, const char *delim)
{
	static char *next;
	char *curr;

	if (str)
		next = str;
	if (!next)
		return (NULL);
	curr = next;
	str = strpbrk(next, delim);
	if (str)
	{
		*str = '\0';
		next = str + 1;
	}
	else
		next = NULL;
	return (curr);
}

