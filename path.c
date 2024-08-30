#include "header.h"
/* betty style doc for function _getenv goes there */
/**
 * _getenv - Entry point
 * @name: first arg
 * Return: char *
 */
char *_getenv(const char *name)
{
	int i = 0, name_len;
	char *value, *name_copy;

	name_len = 0;
	while (name[name_len] != '\0')
	{
		name_len++;
	}
	name_copy = malloc(name_len + 1);
	if (name_copy == NULL)
	{
		return (NULL);
	}
	for (i = 0; i <= name_len; i++)
	{
		name_copy[i] = name[i];
	}
	i = 0;
	while (environ[i])
	{
		if (_strstr(environ[i], name_copy) != NULL && environ[i][0] == name[0])
		{
			value = &environ[i][_strlen(name_copy) + 1];
			free(name_copy);
			return (value);
		}
		i++;
	}
	free(name_copy);

	return (NULL);
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
	arr = malloc((len + 1) * sizeof(char *));
	if (arr == NULL)
	{
		return (NULL);
	}
	token = strtok(str, ":");
	while (token != NULL)
	{
		arr[i] = _strdup(token);
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
	arr[i] = NULL;

	return (arr);
}

/* betty style doc for function list_path goes there */
/**
 * list_path - Entry point
 * Return: node *
 */
node *list_path(void)
{
	char *value;
	char **paths;
	int i = 0;
	node *list = NULL, *n, *temp;

	value = _getenv("PATH");
	if (value == NULL)
		return (NULL);
	paths = split_path(value);
	if (paths == NULL)
		return (NULL);

	while (paths[i])
	{
		n = malloc(sizeof(node));
		if (n == NULL)
		{
			while (list)
			{
				temp = list;
				list = list->next;
				free(temp->str);
				free(temp);
			}
			for (i = 0; paths[i]; i++)
			{
				free(paths[i]);
			}
			free(paths);
			return (NULL);
		}
		n->str = paths[i];
		n->next = list;
		list = n;
		i++;
	}
	free(paths);
	return (list);
}

/* betty style doc for function check_path goes there */
/**
 * check_path - Entry point
 * @path: first arg
 * Return: int
 */
int check_path(char *path)
{
	if (access(path, F_OK) == 0)
	{
		return (0);
	}

	return (-1);
}

