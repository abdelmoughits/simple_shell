#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "main.h"
/**
 *my_strlen - Counting the length of a string
 *@str: astring pointer
 *Return: the lenght
 */
size_t my_strlen(const char *str)
{
	size_t length = 0;

	while (str[length] != '\0')
	{
		length++;
	}
	return (length);
}
/**
 * getPathFromEnvironment - Get the list of PATH
 * Return: pointer to it
 */
char *getPathFromEnvironment(void)
{
	char *path = NULL;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		path = environ[i];
		if (path[0] == 'P' &&
				path[1] == 'A' &&
				path[2] == 'T' &&
				path[3] == 'H' &&
				path[4] == '=')
		{
			path = environ[i] + 5;
			break;
		}
	}
	return (path);
}
/**
 * env - The env displayment info function
 * Return: nothing
 */
void env(void)
{
	int i, b = 0;

	for (i = 0; environ[i] != NULL; i++)
	{
		b = my_strlen(environ[i]);
		write(STDOUT_FILENO, environ[i], b);
		write(STDOUT_FILENO, "\n", 1);
	}
}
/**
 * shek_file - Sheck and search on the path of the argument
 * @line: pointer of type char
 * Return: a pointer to the new path
 */
char *shek_file(char *line)
{
	char *argument;
	char *path;
	char arg[1024];
	int b = 0, i = 0, c = 0;

	path = getPathFromEnvironment();
	while (path[i] != '\0')
	{
		argument = arg;
		for (b = 0 ; path[i] != ':' && path[i] != '\0' ; b++)
		{
			arg[b] = path[i];
			i++;
		}
		arg[b] = '/';
		b++;
		for (c = 0 ; line[c] != '\0' && line[c] != ' ' ; c++)
		{
			arg[c + b] = line[c];
		}
		arg[c + b] = '\0';
		if (access(argument, X_OK) != -1)
		{
			i = my_strlen(arg);
			argument = NULL;
			argument = malloc((i + 1) * sizeof(char));
			for (b = 0 ; arg[b] != '\0' ; b++)
			{
				argument[b] = arg[b];
			}
			argument[b] = '\0';
			return (argument);
		}
		i++;
	}
	return (NULL);
}
