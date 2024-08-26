#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#define _GNU_SOURCE
#define BUFFER_SIZE 1024
#define INITIAL_LINE_SIZE 128

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h> /* You need to recode this library's functions*/
#include <stdbool.h>


/**
 * struct node - singly linked list
 * @str: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct node
{
	char *str;
	struct node *next;
} node;

extern char **environ;

/*string_functions.c */
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
char *_strstr(char *haystack, char *needle);

/* shell.c */
int non_interact(char **argv, node *list);
void handle_sigint(int sig);

/* prompt_functions.c */
void _print(char *str);
int count_words(char *str);
char *prompt(char **argv, node *list);
char **split_string(char *str);
void free_memory(char *str, char **argv);

/* path.c */
char *_getenv(const char *name);
int count_paths(char *str);
char **split_path(char *str);
node *list_path(void);
int check_path(char *path);

/* _env.c */
int print_env(char **argv);

/* _getline.c*/
int check_input(char **lineptr, size_t *n);
int mem_realloc(size_t lc, size_t ls, char *line, char **lineptr, size_t *n);
ssize_t _getline(char **lineptr, size_t *n, int fd);

/* my_strtok()*/
bool is_delimiter(char c, const char *delimiters);
char *skip_delimiters(char *str, const char *delimiters);
char *find_token_end(char *str, const char *delimiters);
char *my_strtok(char *str, const char *delimiters);

#endif
