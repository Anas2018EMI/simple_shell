#include "header.h"

node *list = NULL;
char *str;

/* betty style doc for function handle_sigint goes there */
/**
 * handle_sigint - - Entry point
 * @sig: first arg
 *
 * Return: void
 */
void handle_sigint(int sig)
{
	(void)sig;

	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		free_list(list);
	}
	_exit(EXIT_SUCCESS);
}

/* betty style doc for function initialize goes there */
/**
 * initialize - Entry point
 * Return: int
 */
int initialize(void)
{
	list = list_path();
	if (list == NULL)
	{
		perror("Memory allocation error !!");
		return (-1);
	}
	return (0);
}

/* betty style doc for function main goes there */
/**
 * main - Entry point
 * @argc: first arg
 * @argv: second arg
 * Return: int
 */

int main(int argc, char **argv)
{
	if (argc < -1)
		return (-1);

	if (isatty(STDIN_FILENO) == 0)
		return (handle_non_interactive(argv)); /* , str */
	else if (isatty(STDIN_FILENO) == 1)

		return (handle_interactive(argv, str));

	return (0);
}

/* betty style doc for function non_interact goes there */
/**
 * non_interact - Entry point
 * @argv: first arg
 * Return: int
 */
int non_interact(char **argv) /* , char *str */
{
	char *path = NULL, *line = NULL;
	char **args = NULL; /* **args2 = NULL; */
	int result, read;	/* i = 0 */
	size_t len = 0;
	int command_count = 0;

	while ((read = getline(&line, &len, stdin)) != -1)
	{
		if (read > 0 && line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
		}
		result = process_input(argv, list, &args, line, command_count);
		if (result == -1)
		{
			free(line);
			return (result);
		}
		if (result != 5)
		{
			if (initialize() == -1)
			{
				return (-1);
			}
			result = execute_command(argv, list, path, args, line);
			free_list(list);
		}
		else
			result = 0;
		if (args)
		{
			free_args(args);
			args = NULL;
		}
		command_count++;
	}
	free(line);
	return (result);
}

/* betty style doc for function handle_interactive goes there */
/**
 * handle_interactive - Entry point
 * @argv: first arg
 * @str: third arg
 * Return: int
 */
int handle_interactive(char **argv, char *str) /**/
{
	signal(SIGINT, handle_sigint);
	if (initialize() == -1)
		return (-1);
	while (1)
	{
		if (process_command(argv, list, str) == -1)
			break;
	}

	free_list(list);
	return (0);
}

