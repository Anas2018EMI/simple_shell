#include "header.h"

/* betty style doc for function free_mem goes there */
/**
 * free_mem - Entry point
 * @path: first arg
 * @args: second arg
 * @argv: third arg
 * @str: fourth arg
 * Return: void
 */
void free_mem(char *path, char **args, char **argv, char *str)
{
	if (path == args[0])
		free_memory(str, args);
	else
	{
		free_memory(str, args);
		free(path);
	}
	perror(argv[0]);
}


/* betty style doc for function execute_process goes there */
/**
 * execute_process - Entry point
 * @path: first arg
 * @as: second arg
 * @av: third arg
 * @cpid: fourth arg
 * @str: fifth arg
 * Return: void
 */
void execute_process(char *path, char **as, char **av, pid_t *cpid, char *str)
{
	int execute,status; /*  */

	if (*cpid == 0)
	{
		/* printf("path in execute_process: %s\n", path); */

		execute = execve(path, as, environ);
		if (execute == -1)
		{
			perror(av[0]);
		}
	}
	else
	{
		waitpid(*cpid, &status, 0);
	}

	if (path == as[0])
	{
		free_memory(str, as);
	}
	else
	{
		free_memory(str, as);
		free(path);
	}
}

/* betty style doc for function execute_process goes there */
/**
 * execute_process - Entry point
 * @path: first arg
 * @as: second arg
 * @av: third arg
 * @cpid: fourth arg
 * @str: fifth arg
 * Return: void
 */
int execute_process2(char *path, char **as, char **av, pid_t *cpid )
{
	int execute, status;

	if (*cpid == 0)
	{
		/* // printf("path in execute_process2: %s\n", path);*/ 

		execute = execve(path, as, environ);
		
		if (execute == -1)
		{
			perror(av[0]);
			exit(EXIT_FAILURE);
		}
		
	}
	else
	{
		waitpid(*cpid, &status, 0);
		
	}

	if (path != as[0])
        free(path);

	return (0);
	
}

/* betty style doc for function free_list goes there */
/**
 * free_list - Entry point
 * @list: first arg
 * Return: void
 */
void free_list(node *list)
{
	node *temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->str);
		free(temp);
	}
}

/* betty style doc for function check_full_path goes there */
/**
 * check_full_path - Entry point
 * @is_exist: first arg
 * @path: second arg
 * @list: third arg
 * @args: fourth arg
 * Return: int
 */
char *check_full_path(int *is_exist, char *path, node *list, char **args)
{
	node *ptr;

	ptr = list;
	while (ptr)
	{
		path = malloc(sizeof(char) * (_strlen(ptr->str) + _strlen(args[0]) + 2));
		if (path == NULL)
		{
			ptr = ptr->next;
			continue;
		}

		path = _strcpy(path, ptr->str);
		_strcpy(path + _strlen(ptr->str), "/");
		_strcpy(path + _strlen(ptr->str) + 1, args[0]);
		/* // printf("Trying this path: %s\n", path); */
		*is_exist = check_path(path);
		if (*is_exist != -1)
		{
			return (path);
		}
		ptr = ptr->next;
		free(path);
	}
	return (NULL);
}

