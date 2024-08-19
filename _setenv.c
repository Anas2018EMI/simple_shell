#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
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
	int i = 0, len_n, len_v, new_var_len, len_env;
	char *new_var;
	char **new_environ;

	if (name == NULL || value == NULL || name[0] == '\0')
	{
		return (-1);
	}
	len_n = strlen(name);
	len_v = strlen(value);
	while (environ[i])
	{
		if (strstr(environ[i], name) != NULL && environ[i][len_n] == '=')
		{
			if (overwrite == 0)
			{
				return (0);
			}
			new_var_len = len_n + len_v + 2;
			new_var = malloc(new_var_len);
			if (new_var == NULL) 
			{
				return (-1);
			}
			strcpy(new_var, name);
			strcat(new_var, "=");
			strcat(new_var, value);
			environ[i] = new_var;
			return (0);
		}
		i++;
	} 
	new_var_len = len_n + len_v + 2;
	new_var = malloc(new_var_len);
	if (new_var == NULL) 
	{
		return (-1);
	}
	strcpy(new_var, name);
	strcat(new_var, "=");
	strcat(new_var, value);
	for (len_env = 0; environ[len_env] != NULL; len_env++);
	new_environ = malloc((len_env + 2) * sizeof(char *));
	if (new_environ == NULL) 
	{
		free(new_var);
		return (-1);
	}
	for (i = 0; i < len_env; i++) 
	{
		new_environ[i] = environ[i];
	}
	new_environ[len_env] = new_var;
	new_environ[len_env + 1] = NULL;
	environ = new_environ;
	return (0);
}

int main(int argc, char **argv)
{
	int overwrite, result;
	char *args[] = {"/bin/bash", NULL};

	if (argc != 4)
	{
		return (-1);
	}
	overwrite = atoi(argv[3]);
	result = _setenv(argv[1], argv[2], overwrite);
	if (result == 0) 
	{

		execve("/bin/bash", args, environ);
	}
	/* if (result == 0) 
	   {
	   printf("%s is set to: %s\n",argv[1], getenv(argv[1]));
	   } 
	   else 
	   {
	   perror("Failed to set environment variable");
	   } */
	return(0);
}
