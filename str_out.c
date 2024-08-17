#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
/* betty style doc for function count_words goes there */
/**
 * count_words - Entry point
 * @str: first arg *
 * Return: int
 */
int count_words(char *str)
{
	int i = 0, len = 0;

	while (*(str + i))
	{
		if (*(str + i) == ' ')
		{
			len++;
		}
		i++;
	}
	return (len + 1);
}
/* betty style doc for function prompt goes there */
/**
 * prompt - Entry point
 *
 * Return: char *
 */
char *prompt(void)
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
		return (line);
	}

	return (NULL);
}
/* betty style doc for function split_string goes there */
/**
 * split_string - Entry point
 * @str: first arg
 * Return: char **
 */
char **split_string(char *str)
{
	int i = 0, len;
	char *token;
	char **arr;

	len = count_words(str);
	arr = malloc((len + 1) * sizeof(char *));
	if (arr == NULL)
	{
		return (NULL);
	}
	token = strtok(str, " ");
	i = 0;
	while (token != NULL)
	{
		arr[i] = malloc(strlen(token) + 1);
		if (arr[i] == NULL)
		{
			free(arr);
			return (NULL);
		}
		strcpy(arr[i], token);
		token = strtok(NULL, " ");
		i++;
	}
	arr[len] = NULL;

	return (arr);
}
/* betty style doc for function main goes there */
/**
 * main - Entry point
 * Return: int
 */
int main(void)
{
	char *str;
	int len, i;
	char **arr;

	str = prompt();
	len = count_words(str);
	arr = malloc((len + 1) * sizeof(char *));
	if (arr == NULL)
	{
		return (-1);
	}
	arr = split_string(str);
	for (i = 0; i < len; i++)
	{
		printf("%s\n", arr[i]);
	}
	free(arr);
	return (0);
}
