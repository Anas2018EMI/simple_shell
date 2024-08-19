#include <stdio.h>
#include <unistd.h>
#include <string.h>
extern char **environ;
/* betty style doc for function _setenv goes there */
/**
 * _setenv - Entry point
 * @name: first arg
 * @value: second arg
 * @overwrite: third arg
 * Return: int
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int i = 0, len_n, len_v;
	char * value;
	
	if (name == NULL || value == NULL || name == "\0")
	{
		return (-1);
	}
	len_n = strlen(name);
	len_v = strlen(value);

	
	
	
	
	while (environ[i])
	{
		if (strstr(environ[i], name) == name[0] && environ[i][len_n] == '=')
		{
			if (overwrite == 0)
			{
				return (0);
			}
			//////////////////////////////////





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
