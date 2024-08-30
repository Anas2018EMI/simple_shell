#include "header.h"
/* betty style doc for function print_env goes there */
/**
 * print_env - Entry point
 * @argv: first arg
 * Return: int
 */
int print_env(char **argv)
{
	int  i = 0; /* i = 0, */
	/* char **my_env; */ 

	if (argv == NULL)
		return (-1);
	while (environ[i] != NULL)
	{
		_print(environ[i]);
		_print("\n");
		i++;
	}
		
		

	/* printf("env_length: %i\n",i);  To be deleted */

	/* my_env = malloc((env_length + 1) * sizeof(char *));
	if (my_env == NULL)
	{
		perror(argv[0]);
		return (-1);
	}
	while (i < env_length)
	{
		my_env[i] = _strdup(environ[i]);
		if (my_env[i] == NULL)
		{
			perror(argv[0]);
			i--;
			while (i-- >= 0)
			{
				free(my_env[i]);
			}
			free(my_env);
			return (-1);
		}
		_print(my_env[i]);
		_print("\n");
		i++;
	}
	i = 0;
	while (i < env_length)
	{
		free(my_env[i]);
		i++;
	}
	free(my_env); */
	return (5);
}

