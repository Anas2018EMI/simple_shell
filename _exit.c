#include "header.h"

/**
 * _atoi - Convert a string to an integer.
 * @s: The string to be converted.
 * Return: The integer value of the string.
 */
int _atoi(char *s)
{
	int sign = 1;
	int digit;
	int result = 0;
	int i = 0;
	int seen_digit = 0;

	while (s[i] != '\0' && s[i] == ' ')
	{
		i++;
	}

	while (s[i] != '\0' && (s[i] == '-' || s[i] == '+'))
	{
		if (s[i] == '-')
		{
			sign = -sign;
		}
		i++;
	}

	while (s[i] >= '0' && s[i] <= '9')
	{
		seen_digit = 1;
		digit = s[i] - '0';
		result = result * 10 + digit;
		i++;
	}

	if (!seen_digit)
	{
		return (0);
	}

	result *= sign;

	return (result);
}

/**
 * _is_digit - checks if a character is a digit
 * @c: character to check
 *
 * Return: 1 if c is a digit and 0 otherwise
 */

int _is_digit(char c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}

	return (0);
}

/**
 * handle_exit - Handles the "exit" built-in command for the shell.
 * @str: string typed to shell
 * @args: An array of strings representing the command and its arguments.
 * @list: An array of strings representing the environment variables.
 * @cc: fourth argument
 */

void handle_exit(char *str, char **args, node *list, int cc)
{
	int exit_status = 0, i = 0;

	if (args[1] != NULL)
	{
		for (i = 0; args[1][i] != '\0'; i++)
		{
			if (_is_digit(args[1][i]) == 0)
			{
				perror(args[0]);
				free_memory(str, args);
				if (isatty(STDIN_FILENO) == 1)
					free_list(list);
				exit(2);
			}
		}
		exit_status = _atoi(args[1]);
	}
	if (isatty(STDIN_FILENO) == 1)
	{
		free_memory(str, args);
		free_list(list);
		exit(exit_status);
	}
	else if (isatty(STDIN_FILENO) == 0)
	{
		if (args[1] != NULL)
		{
			free_args(args);
			free(str);
			exit(exit_status);
		}
		else
		{
			free_args(args);
			free(str);
			if (cc == 0)
				exit(0);
			exit(2);
		}
	}
}
