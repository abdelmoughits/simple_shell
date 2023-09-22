#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "main.h"
char **command_list(char *line, char *command);
void free_all(char **arg);
char *S_f_S(char *line, char cH);
void free_all(char **arg);
char *inputBuffer;
/**
 * sighandler - the signel handler function
 * @signal: variable used
 * Return: nothing
 */
void sighandler(int signal)
{
	(void)signal;
	if (inputBuffer != NULL)
	{
		free(inputBuffer);
	}
	exit(0); }
/**
 * *non_interactive_mode - The firdte part of shell
 * @argv: list of commands
 * Return: intiger for succes
 */
int non_interactive_mode(char **argv)
{
	int num = 0;
	int status;
	char **argLISTE;
	char *line;
	size_t len = 0;
	ssize_t size = 0;

	while (size != -1)
	{
		num = 0;
		size = getline(&line, &len, stdin);
		if (size == -1)
		{
			return (0); }
		line[size - 1] = '\0';
		if (access(line, X_OK) == -1)
		{
			write(STDERR_FILENO, argv[0], my_strlen(argv[0]));
			write(STDERR_FILENO, ": 1: ", 5);
			write(STDERR_FILENO, line, size - 1);
			write(STDERR_FILENO, ": not found", 11);
			write(STDERR_FILENO, "\n", 1);
			free(line);
			return (0); }
		argLISTE = command_list(line, line);
		num = fork();
		if (num == 0)
		{
			num = execve(line, argLISTE, NULL);
			if (num == -1)
			{
				perror("Error execve");
				free(line);
				exit(EXIT_FAILURE); }}
		else
		{
			num = wait(&status);
			if (num == -1)
			{
				perror("Error wait"); }}
		free(line); }
	return (0);
}
/**
 * *interactive_mode - The seconde part of shell
 * *Return: intiger value
 */
int interactive_mode(void)
{
	int num = 0;
	int status;
	char *command = NULL;
	char *msg = "Error in input\n";
	char *o_msg = "./shell: No such file or directory\n";
	char **argLISTE;
	char *line = NULL;
	size_t len = 0;
	ssize_t size = 0;

	/**inputBuffer = line;
	signal(SIGINT, sighandler);*/
	while (1)
	{

		command = NULL;
		line = NULL;
		num = 0;
		write(1, "($) ", 4);
		size = getline(&line, &len, stdin);
		/*inputBuffer = line;*/
		if (size == -1)
		{
			write(STDERR_FILENO, msg, my_strlen(msg) + 1);
			continue; }
		if (line[0] == '\n')
		{
			continue; }
		line[size - 1] = '\0';
		if (line[0] == 'e' && line[1] == 'x' && line[2] == 'i' &&
				line[3] == 't' &&
				line[4] == '\0')
		{
			free(line);
			exit(0); }
		if (line[0] == 'e' && line[1] == 'n' && line[2] == 'v' && line[3] == '\0')
		{
			env();
			free(line);
			continue; }
		command = S_f_S(line, ' ');
		if (access(command, X_OK) == -1)
		{
			free(command);
			command = NULL;
			command = shek_file(line);
			if (command == NULL)
			{
				write(1, o_msg, my_strlen(o_msg));
				free(line);
				continue; }}
		argLISTE = command_list(line, command);
		if (!argLISTE)
		{
			free(line);
			return (-1);
		}
		num = fork();
		if (num == 0)
		{
			num = execve(command, argLISTE, NULL);
			if (num == -1)
			{
				perror("Error execve");
				free(line);
				free_all(argLISTE);
				return (-1); }}
		else
		{
			num = wait(&status);
			if (num == -1)
			{
				perror("Error wait"); }
			free(line);
			free_all(argLISTE); }}
}
/**
 * command_list - creat a list of pointers
 * @line: the line of commands
 * @command: the path of command
 * Return: pointer to list
 */
char **command_list(char *line, char *command)
{
	char *change;
	int i = 0, size = 0, index = 0;
	char **arglist = NULL;

	for (index = 0 ; line[index] != '\0' ; index++)
	{
		if (line[index] == ' ')
		{
			i = 0; }
		if (line[index] != ' ' && i == 0)
		{
			i = 1;
			size++; }}
	size++;
	index = 0;
	arglist = malloc(size * sizeof(char *));
	if (arglist == NULL)
	{
		free(command);
		return (NULL); }
	arglist[0] = command;
	arglist[size - 1] = NULL;
	size = 0;
	for (index = 0 ; line[index] != ' ' && line[index] != '\0' ; index++)
	{}
	while (line[index] != '\0')
	{
		if (line[index] == ' ')
		{
			index++;
			continue; }
		size++;
		arglist[size] = NULL;
		for (i = 0 ; line[index + i] != '\0' && line[index + i] != ' ' ; i++)
		{}
		arglist[size] = malloc((i + 1) * sizeof(char));
		change = arglist[size];
		if (arglist[size] == NULL)
		{
			free_all(arglist);
			return (NULL); }
		change[i] = '\0';
		i = 0;
		for (index = index ; line[index] != '\0' && line[index] != ' ' ; index++)
		{
			change[i] = line[index];
			i++;
		}
	}
	return (arglist);
}
/**
 *free_all - free all pointers
 *@arg: a pointer of pointer
 *Return: nothing
 */
void free_all(char **arg)
{
	int i;

	for (i = 0 ; arg[i] != NULL ; i++)
	{
		free(arg[i]); }
	free(arg);
}
