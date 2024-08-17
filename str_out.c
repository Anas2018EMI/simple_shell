#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
/* betty style doc for function count_word goes there */
/**
 * count_word - Entry point
 *
 * Return: Always return 0
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
/* betty style doc for function main goes there */
/**
 * prompt - Entry point
 *
 * Return: Always return 0
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
/* betty style doc for function main goes there */
/**
 * prompt - Entry point
 *
 * Return: Always return 0
 */
char **split_string(char *str)
{
	int i = 0, len;
	char* token;
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

int main()
{
	char *str;
	int len, i;
	char** arr;

	str = prompt();
	len = count_words(str);
	arr = malloc((len + 1) * sizeof(char *));
        if (arr == NULL)
        {
                return (NULL);
        }
	arr = split_string(char *str);
	for (i = 0; i < len + 1; i++)
	{
		printf("%s\n", arr[i]);
	}
}
