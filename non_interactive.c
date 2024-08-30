#include "header.h"

/* betty style doc for function process_input goes there */
/**
 * process_input - Entry point
 * @argv: first arg
 * @list: second arg
 * @args: third arg
 * @line: fourth arg
 * @cc: fourth arg
 * Return: int
 */
int process_input(char **argv, node *list, char ***args, char *line, int cc)
{
	handle_comments(line);
	if (_strcmp(line, "\0") == 0)
	{
		free(line);
		return (0);
	}

	*args = split_string(line);
	if (*args == NULL)
	{
		free(line);
		perror(argv[0]);
		return (-1);
	}

	return (handle_builtin2(argv, list, *args, line, cc));
}

/* betty style doc for function handle_builtin2 goes there */
/**
 * handle_builtin2 - Entry point
 * @argv: first arg
 * @list: second arg
 * @args: third arg
 * @line: fourth arg
 * @cc: fifth arg
 * Return: int
 */
int handle_builtin2(char **argv, node *list, char **args, char *line, int cc)
{
	int env_var;

	if (args[0] != NULL && _strcmp(args[0], "env") == 0)
	{
		env_var = print_env(argv);
		return (env_var);
	}

	if (args[0] != NULL && _strcmp(args[0], "exit") == 0)
	{
		handle_exit(line, args, list, cc);
	}

	return (cc);
}

/* betty style doc for function execute_command goes there */
/**
 * execute_command - Entry point
 * @av: first arg
 * @list: second arg
 * @path: third arg
 * @as: fourth arg
 * @line: fifth arg
 * Return: int
 */
int execute_command(char **av, node *list, char *path, char **as, char *line)
{
	int is_exist;
	pid_t child_pid, out;

	is_exist = check_path(as[0]);
	if (is_exist == -1)
	{
		if (h_pnf(av, list, &path, as, &is_exist, line) == -1)
			return (-1);
	}
	else
	{
		path = as[0];
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		return (-1);
	}
	out = execute_process2(path, as, av, &child_pid);
	return (out);
}
/* betty style doc for function h_pnf goes there */
/**
 * h_pnf - Entry point
 * @av: first arg
 * @list: second arg
 * @path: third arg
 * @as: fourth arg
 * @is: fifth arg
 * @str: sixth arg
 * Return: int
 */
int h_pnf(char **av, node *list, char **path, char **as, int *is, char *str)
{
	char *found_path = check_full_path(is, *path, list, as);

	if (found_path != NULL)
		*path = found_path;
	if (*is == -1)
	{
		perror(av[0]);
		free_memory(str, as);
		return (-1);
	}

	return (0);
}
