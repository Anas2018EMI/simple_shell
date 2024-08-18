#include <stdio.h>
#include <unistd.h>

extern char **environ;
/**
 * main - stat example
 *
 * Return: Always 0.
 */
int main(void)
{
	int i = 0;

	while (environ[i])
	{
		printf("%s\n",environ[i]);
		i++;
	}
	return (0);
}
