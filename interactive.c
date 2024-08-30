#include "header.h"

/* betty style doc for function handle_non_interactive goes there */
/**
 * handle_non_interactive - Entry point
 * @argv: first arg
 * Return: int
 */
int handle_non_interactive(char **argv) /* , char *str */
{
	int interact;

	interact = non_interact(argv); /* , str */

	return (interact);
}
/* betty style doc for function free_args goes there */
/**
 * free_args - Entry point
 * @args: first arg
 * Return: void
 */
void free_args(char **args)
{
	int i;

	if (args == NULL)
		return;

	for (i = 0; args[i] != NULL; i++)
	{
		free(args[i]);
	}
	free(args);
}

/* betty style doc for function process_command goes there */
/**
 * process_command - Entry point
 * @argv: first arg
 * @list: second arg
 * @str: third arg
 * Return: int
 */
int process_command(char **argv, node *list, char *str)
{
	char **args;

	str = prompt(argv, list);
	if (str == NULL || str[0] == '\0')
	{
		free(str);
		return (0);
	}

	handle_comments(str);
	if (_strcmp(str, "\0") == 0)
	{
		free(str);
		return (0);
	}

	args = split_string(str);
	if (args == NULL)
	{
		free(str);
		perror("Memory allocation error");
		return (0);
	}

	if (handle_builtin_commands(args, argv, list, str) == 0)
		return (0);

	return (execute_external_command(args, argv, list, str));
}

/* betty style doc for function handle_builtin_commands goes there */
/**
 * handle_builtin_commands - Entry point
 * @args: first arg
 * @argv: second argument
 * @list: third arg
 * @str: fourth arg
 * Return: int
 */
int handle_builtin_commands(char **args, char **argv, node *list, char *str)
{
	if (args[0] == NULL)
		return (1);

	if (_strcmp(args[0], "env") == 0)
	{
		print_env(argv);
		free_memory(str, args);
		return (0);
	}

	if (_strcmp(args[0], "exit") == 0)
	{
		handle_exit(str, args, list, 0);
		return (0);
	}

	return (1);
}

/* betty style doc for function execute_external_command goes there */
/**
 * execute_external_command - Entry point
 * @args: first arg
 * @argv: second argument
 * @list: third arg
 * @str: fourth arg
 * Return: int
 */
int execute_external_command(char **args, char **argv, node *list, char *str)
{
	char *path = NULL;
	char *found_path;
	int is_exist;
	pid_t child_pid;

	is_exist = check_path(args[0]);
	if (is_exist == -1)
	{
		found_path = check_full_path(&is_exist, path, list, args);
		if (found_path != NULL)
			path = found_path;
		if (is_exist == -1)
		{
			perror(argv[0]);
			free_memory(str, args);
			return (0);
		}
	}
	else
	{
		path = args[0];
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		free_mem(path, args, argv, str);
		return (0);
	}
	execute_process(path, args, argv, &child_pid, str);
	return (0);
}


