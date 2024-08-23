#include "header.h"

/* volatile sig_atomic_t keep_running = 1; */
node *list = NULL;
char *str;

/* betty style doc for function main goes there */
/**
 * main - Entry point
 * @argc: first arg
 * @argv: second arg
 * Return: int
 */

int main(int argc, char **argv)
{
    pid_t child_pid;
    int execute, status, is_exist, interact;
    char **args;
    char *path;       /* *str, *path0*/
    node *ptr, *temp; /* *list = NULL,*/

    if (argc < 0)
        return (-1);

    signal(SIGINT, handle_sigint);

    list = list_path();
    if (list == NULL)
    {
        perror("Memory allocation error");
        return (-1);
    }
    if (isatty(STDIN_FILENO) == 0)
    {
        interact = non_interact(argv, list);
        while (list)
        {
            temp = list;
            list = list->next;
            free(temp->str);
            free(temp);
        }
        return (interact);
    }
    else if (isatty(STDIN_FILENO) == 1)
    {
        while (1) /* keep_running */
        {
            path = NULL;
            /* ptr->next = NULL; */

            str = prompt(argv, list);
            if (str == NULL || str[0] == '\0')
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

            if (args[0] != NULL && strcmp(args[0], "env") == 0)
            {
                print_env();
                free_memory(str, args);
                continue;
            }

            if (args[0] != NULL && strcmp(args[0], "exit") == 0)
            {
                free_memory(str, args);

                while (list)
                {
                    temp = list;
                    list = list->next;
                    free(temp->str);
                    free(temp);
                }

                exit(0);
            }

            is_exist = check_path(args[0]);
            if (is_exist == -1)
            {
                ptr = list;
                while (ptr)
                {
                    path = malloc(sizeof(char) * (strlen(ptr->str) + strlen(args[0]) + 2));
                    if (path == NULL)
                    {
                        ptr = ptr->next;
                        continue;
                    }
                    path = strcpy(path, ptr->str);
                    path = strcat(path, "/");
                    path = strcat(path, args[0]);
                    printf("Trying this path: %s\n", path); /* Delete this line*/
                    is_exist = check_path(path);
                    if (is_exist != -1)
                    {
                        /* path = path0; */
                        break;
                    }
                    ptr = ptr->next;
                    free(path);
                }
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
                if (path == args[0])
                {
                    free_memory(str, args);
                }
                else
                {
                    free_memory(str, args);
                    free(path);
                }
                perror(argv[0]);
                continue;
            }
            if (child_pid == 0)
            {
                execute = execve(path, args, environ);
                if (execute == -1)
                {
                    perror(argv[0]);
                }
            }
            else
            {
                waitpid(child_pid, &status, 0);
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
    }
    while (list)
    {
        temp = list;
        list = list->next;
        free(temp->str);
        free(temp);
    }

    return (0);
}
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
        node *temp;

        /* keep_running = 0; */
        /* free(str); */
        write(STDOUT_FILENO, "\n", 1);
        while (list)
        {
            temp = list;
            list = list->next;
            free(temp->str);
            free(temp);
        }
    }
    _exit(EXIT_SUCCESS);
}

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
    int execute, status, is_exist;
    char **args;
    char *str, *path;
    node *ptr, *temp;

    str = prompt(argv, list);
    if (str == NULL)
        return (-1);
    args = split_string(str);
    if (args == NULL)
    {
        free(str);
        perror("Memory allocation error");
        return (-1);
    }
    if (args[0] != NULL && strcmp(args[0], "env") == 0)
    {
        print_env();
        free_memory(str, args);
        return(0);
    }

    if (args[0] != NULL && strcmp(args[0], "exit") == 0)
    {
        free_memory(str, args);

        while (list)
        {
            temp = list;
            list = list->next;
            free(temp->str);
            free(temp);
        }

        exit(0);
    }
    is_exist = check_path(args[0]);
    if (is_exist == -1)
    {
        ptr = list;
        while (ptr)
        {
            path = malloc(sizeof(char) * (strlen(ptr->str) + strlen(args[0]) + 2));
            if (path == NULL)
            {
                ptr = ptr->next;
                continue;
            }
            path = strcpy(path, ptr->str);
            path = strcat(path, "/");
            path = strcat(path, args[0]);
            printf("Trying this path: %s\n", path); /* Delete this line*/
            is_exist = check_path(path);
            if (is_exist != -1)
            {
                /* path = path0;*/
                break;
            }

            ptr = ptr->next;
            free(path);
        }
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
        if (path == args[0])
        {
            free_memory(str, args);
        }
        else
        {
            free_memory(str, args);
            free(path);
        }
        perror(argv[0]);
        return (-1);
    }
    if (child_pid == 0)
    {
        execute = execve(path, args, environ);
        if (execute == -1)
        {
            if (path == args[0])
            {
                free_memory(str, args);
            }
            else
            {
                free_memory(str, args);
                free(path);
            }
            perror(argv[0]);
            return (-1);
        }
    }
    else
    {
        waitpid(child_pid, &status, 0);
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
    return (0);
}
