#include <stdio.h>
#include <unistd.h>
#include <string.h>
extern char **environ;
/* betty style doc for function _getenv goes there */
/**
 * _getenv - Entry point
 * @name: first arg
 * Return: char *
 */
char *_getenv(const char *name)
{
	int i = 0;
	char * value;
	
	while (environ[i])
	{
		if (strstr(environ[i], name) != NULL)
		{
			value = &environ[i][strlen(name) + 1];
			return (value);
		}
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	char *value;
	
	if (argc != 2)
	{
		return (-1);
	}
	value = _getenv(argv[1]);
	if (value != NULL)
	{
		printf("%s\n", value);
	}

	return (0);
}
