#include "main.h"
/**
 *main - simple shell function
 *@argc: the number of arguments
 *@argv: arguments list
 *Return: 0 in succes
 */
int main(int __attribute__((unused)) argc, char *argv[])
{
	if (!isatty(STDIN_FILENO))
	{
		non_interactive_mode(argv);
	}
	else
	{
		interactive_mode();
	}
	return (0);
}
/**
 * S_f_S - Creat a new a buffer for the first command
 * @line: the command line
 * @cH: the signe of coping end
 * Return: a pointer to the created buffer
 */
char *S_f_S(char *line, char cH)
{
	char *arg;
	int c;

	arg = NULL;
	for (c = 0 ; line[c] != '\0' && line[c] != cH ; c++)
	{}
	arg = malloc((c + 1) * sizeof(char));
	if (arg == NULL)
	{
		return (NULL); }
	for (c = 0 ; line[c] != '\0' && line[c] != cH ; c++)
	{
		arg[c] = line[c]; }
	arg[c] = '\0';
	return (arg);
}
