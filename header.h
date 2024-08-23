#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h> /* You need to recode this library's functions*/

/**
 * struct list_s - singly linked list
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

#endif
