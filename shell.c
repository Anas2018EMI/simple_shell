#include "header.h"

/* volatile sig_atomic_t keep_running = 1; */
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
 * @argc: first arg
 * Return: int
 */
int initialize(int argc) /* , node *lis*/
{
	if (argc < 0)
		return (-1);
	list = list_path();
	if (list == NULL)
	{
		perror("Memory allocation error");
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
	if (initialize(argc) == -1)
		return (-1);

	if (isatty(STDIN_FILENO) == 0)
		return (handle_non_interactive(argv, list, str));
	else if (isatty(STDIN_FILENO) == 1)

		return (handle_interactive(argv, list, str));

	return (0);
}

/* betty style doc for function non_interact goes there */
/**
 * non_interact - Entry point
 * @argv: first arg
 * @list: second arg
 * @str: third arg
 * Return: int
 */
int non_interact(char **argv, node *list, char *str)
{
	char *path = NULL;
	char **args;
	int result;

	str = prompt(argv, list);
	if (str == NULL)
		return (-1);

	result = process_input(argv, list, &args, str);
	if (result != 0)
		return (result);

	return (execute_command(argv, list, path, args, str));
}

