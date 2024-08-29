#include "header.h"
/* betty style doc for function _print goes there */
/**
 * _print - Entry point
 * @str: first arg
 * Return: void
 */
void _print(char *str)
{
	int i = 0;

	while (*(str + i))
	{
		write(1, &str[i], 1);
		i++;
	}
	fflush(stdout);
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
 * @argv: first arg
 * @list: second arg
 * Return: char *
 */
char *prompt(char **argv, node *list)
{
	char *terminal = "", *line = NULL;
	size_t len = 0;
	ssize_t nread;
	node *temp;
	int i = 0;

	_print(terminal);
	nread = _getline(&line, &len, STDIN_FILENO);
	if (nread == -1) /* End of File condition*/
	{
		perror(argv[0]);
		free(line);
		while (list)
		{
			temp = list;
			list = list->next;
			free(temp->str);
			free(temp);
		}
		exit(EXIT_FAILURE); /* End of File condition   return (NULL)*/
	}

	while (line[i] != '\0')
	{
		if (line[i] == '\n')
			break;
		i++;
	}
	line[i] = '\0';
	/* line[nread - 1] = '\0'; */
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
	token = my_strtok(str, " ");
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
		token = my_strtok(NULL, " ");
		i++;
	}
	arr[i] = NULL;

	return (arr);
}
/* betty style doc for function free_memory goes there */
/**
 * free_memory - Entry point
 * @str: first arg
 * @argv: second arg
 * Return: void
 */
void free_memory(char *str, char **argv)
{
	int i;

	free(str);
	for (i = 0; argv[i] != NULL; i++)
	{
		free(argv[i]);
	}
	free(argv);
}

