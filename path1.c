#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
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
/* betty style doc for function count_paths goes there */
/**
 * count_paths - Entry point
 * @str: first arg *
 * Return: int
 */
int count_paths(char *str)
{
	int i = 0, len = 0;

	while (*(str + i))
	{
		if (*(str + i) == ':' && (i == 0 || str[i - 1] != ':'))
		{
			len++;
		}
		i++;
	}
	if (i > 0 && str[i - 1] != ':')
	{
		len++;
	}
	return (len);
}
/* betty style doc for function split_path goes there */
/**
 * split_path - Entry point
 * @str: first arg
 * Return: char **
 */
char **split_path(char *str)
{
	int i = 0, len, j;
	char *token;
	char **arr;

	len = count_paths(str);
	arr = malloc(len * sizeof(char *));
	if (arr == NULL)
	{
		return (NULL);
	}
	token = strtok(str, ":");
	while (token != NULL)
	{
		arr[i] = strdup(token);
		if (arr[i] == NULL)
		{
			for (j = 0; j < i; j++)
			{
				free(arr[j]);
			}
			free(arr);
			return (NULL);
		}
		token = strtok(NULL, ":");
		i++;
	}
	arr[len] = NULL;

	return (arr);
}

/* betty style doc for function  goes there */
/**
 * print_path - Entry point
 * Return: void
 */
void print_path(void)
{
	char *value;
	char **paths;
	int i = 0;

	value = _getenv("PATH");
	paths = malloc(count_paths(value) * sizeof(char *));
	if (paths == NULL)
	{
		exit(EXIT_FAILURE);
	}
	paths = split_path(value);
	if (paths != NULL)
	{
		while (paths[i])
		{
			printf("%s\n", paths[i]);
			i++;
		}
	}

}
int main(void)
{
	print_path();

	return (0);
}
