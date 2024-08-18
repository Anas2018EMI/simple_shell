#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int count_words(char *str);
char *prompt(void);
char **split_string(char *str);
/* int execute_command(pid_t child_pid, int len, char **arr, int status); */
/* betty style doc for function main goes there */
/**
 * main - Entry point
 * Return: int
 */
int main(void)
{
	pid_t child_pid;
	int status, len, i, execute;
	char **argv;
	char *str;

	while (1)
	{
		str = prompt();
		if (str == NULL)
		{
			continue;
		}
		len = count_words(str);
		argv = split_string(str);
		if (argv == NULL)
		{
			free(str);
			perror("Memory allocation error");
			return (-1);
		}

		child_pid = fork();
		if (child_pid == -1)
		{
			free(str);
			free(argv);
			perror("Error:");
			return (-1);
		}
		if (child_pid == 0)
		{
			for (i = 0; i < len; i++)
			{
				printf("argv[%i]=%s\n", i, argv[i]);
			}
			execute = execve(argv[0], argv, NULL);
			if (execute == -1)
			{
				perror("Error:");
				free(str);
				free(argv);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
			printf("Oh, it's all better now\n");
		}

		free(str);
		for (i = 0; argv[i] != NULL; i++)
		{
			free(argv[i]);
		}
		free(argv);
	}
	return (0);
}

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
		if (*(str + i) == ' ' && (i == 0 || str[i - 1] != ' '))
		{
			len++;
		}
		i++;
	}
	if (i > 0 && str[i - 1] != ' ')
	{
		len++;
	}
	return (len);
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
	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}
	line[nread - 1] = '\0';
	return (line);
}
/* betty style doc for function split_string goes there */
/**
 * split_string - Entry point
 * @str: first arg
 * Return: char **
 */
char **split_string(char *str)
{
	int i = 0, len, j;
	char *token;
	char **arr;

	len = count_words(str);
	arr = malloc((len + 1) * sizeof(char *));
	if (arr == NULL)
	{
		return (NULL);
	}
	token = strtok(str, " ");
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
		token = strtok(NULL, " ");
		i++;
	}
	arr[len] = NULL;

	return (arr);
}

