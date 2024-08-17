#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
/* betty style doc for function main goes there */
/**
 * prompt - Entry point
 *
 * Return: Always return 0
 */
int prompt(void)
{
	int i = 0;
	char *terminal = "$ ", *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (*(terminal + i))
	{
		write(1, &terminal[i], 1);
		i++;
	}
	i = 0;
	nread = getline(&line, &len, stdin);
	if (nread != -1)
	{
		while (*(line + i))
		{
			write(1, &line[i], 1);
			i++;
		}
	}

	free(line);

	return (0);
}
