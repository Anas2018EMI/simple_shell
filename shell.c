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

/* betty style doc for function free_mem goes there */
/**
 * free_mem - Entry point
 * @path: first arg
 * @args: second arg
 * @argv: third arg
 * Return: void
 */
void free_mem(char *path, char **args, char **argv)
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

/* betty style doc for function initialize goes there */
/**
 * initialize - Entry point
 * @argc: first arg
 * Return: int
 */
int initialize(int argc)
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

/* betty style doc for function execute_process goes there */
/**
 * execute_process - Entry point
 * @path: first arg
 * @args: second arg
 * @argv: third arg
 * @child_pid: fourth arg
 * Return: void
 */
void execute_process(char *path, char **args, char **argv, pid_t *child_pid)
{
    int execute, status;

    if (*child_pid == 0)
    {
        execute = execve(path, args, environ);
        if (execute == -1)
        {
            perror(argv[0]);
        }
    }
    else
    {
        waitpid(*child_pid, &status, 0);
    }

    if (path == args[0])
    {
        free_memory(str, args);
    }
    else
    {
        free_memory(str, args);
        free(path);
    }
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
        *is_exist = check_path(path);
        if (*is_exist != -1)
        {
            return (path);
            break;
        }
        ptr = ptr->next;
        free(path);
    }
    return (NULL);
}

/*//////////////////////////////////////////////////////////////////////////////*/

int handle_builtin_commands(char *str, char **args, char **argv, node *list)
{
    int env_var;

    if (args[0] != NULL && _strcmp(args[0], "env") == 0)
    {
        env_var = print_env(argv);
        free_memory(str, args);
        return (env_var > 0);
    }
    if (args[0] != NULL && _strcmp(args[0], "exit") == 0)
    {
        handle_exit(str, args, list);
        return 1;
    }
    return 0;
}

int process_command(char *str, char **args, char **argv, node *list)
{
    int is_exist;
    char *path = NULL, *found_path;

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
            return 1;
        }
    }
    else
    {
        path = args[0];
    }
    return (fork_and_execute(path, args, argv));
}

int fork_and_execute(char *path, char **args, char **argv)
{
    pid_t child_pid = fork();
    if (child_pid == -1)
    {
        free_mem(path, args, argv);
        return 1;
    }
    execute_process(path, args, argv, &child_pid);
    return 0;
}

int interactive_mode(char **argv, node *list)
{
    char **args;

    while (1)
    {
        str = prompt(argv, list);
        if (str == NULL || str[0] == '\0')
        {
            free(str);
            continue;
        }
        handle_comments(str);
        if (_strcmp(str, "\0") == 0)
        {
            free(str);
            continue;
        }
        args = split_string(str);
        if (args == NULL)
        {
            free(str);
            perror("Memory allocation error");
            continue;
        }
        if (handle_builtin_commands(str, args, argv, list))
            continue;
        if (process_command(str, args, argv, list))
            continue;
    }
    return 0;
}

int main(int argc, char **argv)
{
    signal(SIGINT, handle_sigint);
    if (initialize(argc) == -1)
        return (-1);

    if (isatty(STDIN_FILENO) == 0)
    {
        int interact = non_interact(argv, list);
        free_list(list);
        return (interact);
    }
    else if (isatty(STDIN_FILENO) == 1)
    {
        int result = interactive_mode(argv, list);
        free_list(list);
        return result;
    }

    free_list(list);
    return (0);
}
/*//////////////////////////////////////////////////////////////////////////////*/

/* betty style doc for function main goes there */
/**
 * main - Entry point
 * @argc: first arg
 * @argv: second arg
 * Return: int
 */

/*
int main(int argc, char **argv)
{
    pid_t child_pid;
    int is_exist, interact, env_var;
    char **args;
    char *path, *found_path;

    signal(SIGINT, handle_sigint);
    if (initialize(argc) == -1)
        return (-1);
    if (isatty(STDIN_FILENO) == 0)
    {
        interact = non_interact(argv, list);
        free_list(list);
        return (interact);
    }
    else if (isatty(STDIN_FILENO) == 1)
    {
        while (1)
        {
            path = NULL;
            str = prompt(argv, list);
            if (str == NULL || str[0] == '\0')
            {
                free(str);
                continue;
            }
            handle_comments(str);
            if (_strcmp(str, "\0") == 0)
            {
                free(str);
                continue;
            }
            args = split_string(str);
            if (args == NULL)
            {
                free(str);
                perror("Memory allocation error");
                continue;
            }
            if (args[0] != NULL && _strcmp(args[0], "env") == 0)
            {
                env_var = print_env(argv);
                free_memory(str, args);
                if (env_var > 0)   To avoid the error msg of not using env_var
                    continue;
                continue;
            }
            if (args[0] != NULL && _strcmp(args[0], "exit") == 0)
                handle_exit(str, args, list);
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
                    continue;
                }
            }
            else
            {
                path = args[0];
            }
            child_pid = fork();
            if (child_pid == -1)
            {
                free_mem(path, args, argv);
                continue;
            }
            execute_process(path, args, argv, &child_pid);
        }
    }
    free_list(list);
    return (0);
}
*/

/* betty style doc for function non_interact goes there */
/**
 * non_interact - Entry point
 * @argv: first arg
 * @list: second arg
 * Return: int
 */
int non_interact(char **argv, node *list)
{
    pid_t child_pid;
    int is_exist, env_var;
    char **args;
    char *str, *path, *found_path;

    path = NULL;
    str = prompt(argv, list);
    if (str == NULL)
        return (-1);
    handle_comments(str);
    if (_strcmp(str, "\0") == 0)
    {
        free(str);
        return (-1);
    }
    args = split_string(str);
    if (args == NULL)
    {
        free(str);
        perror("Memory allocation error");
        return (-1);
    }
    if (args[0] != NULL && _strcmp(args[0], "env") == 0)
    {
        env_var = print_env(argv);
        free_memory(str, args);
        return (env_var);
    }
    if (args[0] != NULL && _strcmp(args[0], "exit") == 0)
    {
        handle_exit(str, args, list);
    }
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
            return (-1);
        }
    }
    else
    {
        path = args[0];
    }
    child_pid = fork();
    if (child_pid == -1)
    {
        free_mem(path, args, argv);
        return (-1);
    }
    execute_process(path, args, argv, &child_pid);
    return (0);
}
