#include "header.h"
static char *last_token;
/* betty style doc for function is_delimiter goes there */
/**
 * is_delimiter - Entry point
 * @c: first arg
 * @delimiters: second arg
 * Return: bool
 */
bool is_delimiter(char c, const char *delimiters)
{
	while (*delimiters != '\0')
	{
		if (c == *delimiters)
		{
			return (true);
		}
		delimiters++;
	}
	return (false);
}
/* betty style doc for function skip_delimiters goes there */
/**
 * skip_delimiters - Entry point
 * @str: first arg
 * @delimiters: second arg
 * Return: char *
 */

char *skip_delimiters(char *str, const char *delimiters)
{
	if (str == NULL)
	{
		return (NULL);
	}
	while (*str != '\0' && is_delimiter(*str, delimiters))
	{
		str++;
	}
	return (str);
}
/* betty style doc for function find_token_end goes there */
/**
 * find_token_end - Entry point
 * @str: first arg
 * @delimiters: second arg
 * Return: char *
 */

char *find_token_end(char *str, const char *delimiters)
{
	if (str == NULL)
	{
		return (NULL);
	}
	while (*str != '\0' && !is_delimiter(*str, delimiters))
	{
		str++;
	}
	return (str);
}
/* betty style doc for function my_strtok goes there */
/**
 * my_strtok - Entry point
 * @str: first arg
 * @delimiters: second arg
 * Return: char *
 */

char *my_strtok(char *str, const char *delimiters)
{
	char *token_start;

	/* last_token = NULL; */
	if (str == NULL)
	{
		str = last_token;
	}

	str = skip_delimiters(str, delimiters);

	if (str == NULL || *str == '\0')
	{
		last_token = NULL;
		return (NULL);
	}

	token_start = str;
	str = find_token_end(str, delimiters);

	if (*str != '\0')
	{
		*str = '\0';
		last_token = str + 1;
	}
	else
	{
		last_token = NULL;
	}

	return (token_start);
}

