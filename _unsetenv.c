#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
extern char **environ;
/* betty style doc for function  is_exist goes there */
/**
 *  is_exist- Entry point
 * @name: first arg
 * @val: second arg
 * @ow: third arg
 * @len_n: fourth arg
 * @len_v: fifth arg
 * Return: int
 */
int is_exist(const char *name, const char *val, int ow, int len_n, int len_v)
{
	int i = 0, new_var_len;
	char *new_var;

	while (environ[i])
	{
		if (strstr(environ[i], name) != NULL && environ[i][len_n] == '=')
		{
			if (ow == 0)
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
			strcat(new_var, val);
			environ[i] = new_var;
			return (0);
		}
		i++;
	}
	return (-1);
}
/* betty style doc for function create_var goes there */
/**
 * create_var - Entry point
 * @name: first arg
 * @value: second arg
 * @new_var_len: third arg
 * Return: int
 */
int create_var(const char *name, const char *value, int new_var_len)
{
	int i = 0, len_env;
	char *new_var;
	char **new_environ;

	new_var = malloc(new_var_len);
	if (new_var == NULL)
	{
		return (-1);
	}
	strcpy(new_var, name);
	strcat(new_var, "=");
	strcat(new_var, value);
	for (len_env = 0; environ[len_env] != NULL; len_env++)
	{
	}
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
	int len_n, len_v, new_var_len;

	if (name == NULL || value == NULL || name[0] == '\0')
	{
		return (-1);
	}
	len_n = strlen(name);
	len_v = strlen(value);
	if (is_exist(name, value, overwrite, len_n, len_v) != -1)
	{
		return (0);
	}
	new_var_len = len_n + len_v + 2;
	if (create_var(name, value, new_var_len) != -1)
	{
		return (0);
	}

	return (0);
}
/* betty style doc for function  is_exist2 goes there */
/**
 *  is_exist2- Entry point
 * @name: first arg
 * @len_n: fourth arg
 * Return: int
 */
int is_exist2(const char *name, int len_n)
{
	int i = 0;

	while (environ[i])
	{
		if (strstr(environ[i], name) != NULL && environ[i][len_n] == '=')
		{
			return (i);
		}
		i++;
	}
	return (-1);
}
/* betty style doc for function _unsetenv goes there */
/**
 * _unsetenv - Entry point
 * @name: first arg
 * Return: int
 */
int _unsetenv(const char *name)
{
	int len_n, index, len_env, i;
	char **new_environ;

	if (name == NULL || name[0] == '\0')
	{
		return (-1);
	}
	len_n = strlen(name);
	index = is_exist2(name, len_n);
	if (index == -1)
	{
		return (0);
	}
	for (len_env = 0; environ[len_env] != NULL; len_env++)
	{
	}
	new_environ = malloc((len_env + 1) * sizeof(char *));
	if (new_environ == NULL)
	{
		return (-1);
	}
	for (i = 0; i < index; i++)
	{
		new_environ[i] = environ[i];
	}
	for (i = index; i < len_env; i++)
	{
		new_environ[i] = environ[i + 1];
	}

	new_environ[len_env] = NULL;
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
		result = _setenv("DELETE", "Modified Value", overwrite);
		result =  _unsetenv("DELETE");
		execve("/bin/bash", args, environ);
	}
	/* 
	 * if (result == 0) 
	 {
	 printf("%s is set to: %s\n",argv[1], getenv(argv[1]));
	 } 
	 else 
	 {
	 perror("Failed to set environment variable");
	 } 
	 */
	return (0);
}
