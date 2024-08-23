#include "header.h"

void print_env(void)
{
    int i = 0, env_length = 0;
    char **my_env;

    while(environ[env_length] != NULL)
    {
        env_length++;
    }

    my_env = malloc((env_length + 1) * sizeof(char *));
    if (my_env == NULL)
    {
        perror("malloc");
        exit(-1);
    }

    while (i < env_length)
    {
        my_env[i] = strdup(environ[i]);
        if (my_env[i] == NULL)
        {
            perror("strdup");
            i--;
            while (i-- >= 0)
            {
                free(my_env[i]);
            }
            free(my_env);
            exit(-1);
        }
        _print(my_env[i]);
        _print("\n");
        i++;
    }

    i = 0;
    while (i < env_length)
    {
        free(my_env[i]);
        i++;
    }

    free(my_env);
}
