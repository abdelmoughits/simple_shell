#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
/**
 *main - simple shell function
 *@argc: the number of arguments
 *@argv: arguments list
 *Return: 0 in succes
 */
int main(int __attribute__((unused)) argc, char *argv[])
{
	int num = 0;
	int status;
	char *msg = "Error in input\n";
	char *argLISTE[5];
	char *line;
	size_t len = 0;
	ssize_t size = 0;

	if (!isatty(STDIN_FILENO))
	{
		while (size != -1)
		{
			num = 0;
			size = getline(&line, &len, stdin);
			if (size == -1)
			{
				return (0);
			}
			line[size - 1] = '\0';
			if (access(line, X_OK) == -1)
			{
				write(STDERR_FILENO, argv[0], my_strlen(argv[0]));
				write(STDERR_FILENO, ": 1: ", 5);
				write(STDERR_FILENO, line, size - 1);
				write(STDERR_FILENO, ": not found", 11);
				write(STDERR_FILENO, "\n", 1);
				free(line);
				return (0);
			}
			argLISTE[0] = line;
			argLISTE[1] =  NULL;
			num = fork();
			if (num == 0)
			{
				num = execve(line, argLISTE, NULL);
				if (num == -1)
				{
					perror("Error execve");
					free(line);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				num = wait(&status);
				if (num == -1)
				{
					perror("Error wait");
				}
			}
			free(line);
		}
	}
	else
	{
		while (1)
		{
			line = NULL;
			num = 0;
			write(1, "($) ", 4);
			size = getline(&line, &len, stdin);
			if (size == -1)
			{
				write(STDERR_FILENO, msg, my_strlen(msg) + 1);
				continue;
			}
			if (line[0] == '\n')
			{
				continue;
			}
			line[size - 1] = '\0';
			if (access(line, X_OK) == -1)
			{
				perror("./shell");
				free(line);
				continue;
			}
			argLISTE[0] = line;
			argLISTE[1] =  NULL;
			num = fork();
			if (num == 0)
			{
				num = execve(line, argLISTE, NULL);
				if (num == -1)
				{
					perror("Error execve");
					free(line);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				num = wait(&status);
				if (num == -1)
				{
					perror("Error wait");
				}
				free(line);
			}
		}
	}
	return (0);
}
