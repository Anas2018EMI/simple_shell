#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

char *prompt(void);
char **split_string(char *str);
/**
 * main - fork & wait example
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid;
	int status, i;
	char *argv[] = {"/bin/ls", "-l", "/tmp/", NULL};

	while (1)
	{
		prompt();
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			return (1);
		}
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, NULL) == -1)
			{
				perror("Error:");
			}
		}
		else
		{
			wait(&status);
			printf("Oh, it's all better now\n");
		}
	}
	return (0);
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
	char **arr = malloc((len + 2) * sizeof(char *));
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
	arr[len + 1] = NULL;

	return (arr);
}
