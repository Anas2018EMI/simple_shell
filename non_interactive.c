#include "header.h"

/* betty style doc for function process_input goes there */
/**
 * process_input - Entry point
 * @argv: first arg
 * @list: second arg
 * @args: third arg
 * @str: fourth arg
 * Return: int
 */
int process_input(char **argv, node *list, char ***args, char *str)
{
	handle_comments(str);
	if (_strcmp(str, "\0") == 0)
	{
		free(str);
		return (-1);
	}

	*args = split_string(str);
	if (*args == NULL)
	{
		free(str);
		perror("Memory allocation error");
		return (-1);
	}

	return (handle_builtin_commands2(argv, list, *args, str));
}

/* betty style doc for function handle_builtin_commands2 goes there */
/**
 * handle_builtin_commands2 - Entry point
 * @argv: first arg
 * @list: second arg
 * @args: third arg
 * @str: fourth arg
 * Return: int
 */
int handle_builtin_commands2(char **argv, node *list, char **args, char *str)
{
	int env_var;

	if (args[0] != NULL && _strcmp(args[0], "env") == 0)
	{
		env_var = print_env(argv);
		/*free_memory(str, args);*/
		return (env_var);
	}

	if (args[0] != NULL && _strcmp(args[0], "exit") == 0)
	{
		handle_exit(str, args, list);
	}

	return (0);
}

/* betty style doc for function execute_command goes there */
/**
 * execute_command - Entry point
 * @av: first arg
 * @list: second arg
 * @path: third arg
 * @as: fourth arg
 * @str: fifth arg
 * Return: int
 */
int execute_command(char **av, node *list, char *path, char **as, char *str)
{
	int is_exist;
	/* char *found_path; */
	pid_t child_pid;

	is_exist = check_path(as[0]);
	if (is_exist == -1)
	{
		if (h_pnf(av, list, &path, as, &is_exist, str) == -1)
			return (-1);
	}
	else
	{
		path = as[0];
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		free_mem(path, as, av, str);
		return (-1);
	}

	execute_process(path, as, av, &child_pid, str);
	return (0);
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

