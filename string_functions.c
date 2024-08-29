#include "header.h"
/* betty style doc for function _strcmp goes there */
/**
 * _strcmp - Entry point
 *
 * @s2: first arg
 * @s1: second arg
 * Return: dest
 */
int _strcmp(char *s1, char *s2)
{
	int counter = 0, i = 0;

	while (*(s1 + counter) != '\0')
	{
		counter++;
	}
	while (i < counter)
	{
		if (*(s1 + i) != *(s2 + i))
		{
			return (*(s1 + i) - *(s2 + i));
		}
		i++;
	}

	return (0);
}

/* betty style doc for function _strlen goes there */
/**
 * _strlen - Entry point
 *
 * @s: first arg
 * Return: Always 0 (Success)
 */

int _strlen(char *s)
{
	int counter = 0;

	while (*(s + counter) != '\0')
	{
		counter++;
	}

	return (counter);
}

/* betty style doc for function _strcpy goes there */
/**
 * _strcpy - Entry point
 *
 * @src: first arg
 * @dest: second arg
 * Return: dest
 */
char *_strcpy(char *dest, char *src)
{
	int counter = 0;

	while (*(src + counter) != '\0')
	{
		*(dest + counter) = *(src + counter);
		counter++;
	}
	*(dest + counter) = *(src + counter);
	return (dest);
}

/* betty style doc for function _strdup goes there */
/**
 * _strdup - Entry point
 * @str: first arg
 *
 * Return: char *
 */
char *_strdup(char *str)
{
	unsigned int i = 0, j = 0;
	char *ptr;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*(str + i))
	{
		i++;
	}
	ptr = malloc(i + 1);
	if (ptr == NULL)
	{
		return (NULL);
	}

	while (*str)
	{
		*(ptr + j) = *str;
		str++;
		j++;
	}
	*(ptr + j) = *str;
	return (ptr);
}

/* betty style doc for function _strstr goehaystackthere */
/**
 * _strstr - Entry point
 * @haystack: first arg
 * @needle: second arg
 *
 * Return: string
 */
char *_strstr(char *haystack, char *needle)
{
	int i = 0, j = 0, l = 0;
	char *ptr;

	if (*needle == '\0')
	{
		return (haystack);
	}
	while (*(haystack + i) != '\0')
	{
		l = 0;
		j = i;
		while (*(needle + ++l) == *(haystack + ++i) || *(needle + l) == '\0')
		{
			if (*(needle + l) == '\0')
			{
				ptr = &haystack[j];
				return (ptr);
			}
		}
		i = j;
		i++;
	}

	return (NULL);
}
