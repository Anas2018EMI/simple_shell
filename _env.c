#include "header.h"
/* betty style doc for function print_env goes there */
/**
 * print_env - Entry point
 * @argv: first arg
 * Return: int
 */
int print_env(char **argv)
{
	int  i = 0;

	if (argv == NULL)
		return (-1);
	while (environ[i] != NULL)
	{
		_print(environ[i]);
		_print("\n");
		i++;
	}

	return (5);
}

