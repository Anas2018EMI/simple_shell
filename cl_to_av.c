#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* betty style doc for function main goes there */
/**
 * main - Entry point
 * @ac: first arg
 * @str: second arg
 *
 * Return: Always return 0
 */
char** split(char *str)
{
	int i = 0, len = 0;
	char* token;

	while (*(str + i))
	{
		if (*(str + i) == ' ')
		{
			len++;
		}
		i++;
	}
	char **arr = calloc(len + 1, sizeof(char *));
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
	}


	return (arr);
}

int main(void)
{
	int i;
	char**	arr = split("Hello world test!");

	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}

	return (0);
}
