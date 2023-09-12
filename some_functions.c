#include <stdio.h>
/**
 *my_strlen - cuonting the length of a string
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
