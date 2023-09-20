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
