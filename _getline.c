#include "header.h"
/* betty style doc for function check_input goes there */
/**
 * check_input - Entry point
 * @lineptr: first arg
 * @n: second arg
 * Return: int
 */
int check_input(char **lineptr, size_t *n)
{
	if (lineptr == NULL || n == NULL)
		return (-1);
	if (*lineptr == NULL)
	{
		*lineptr = malloc(INITIAL_LINE_SIZE);
		if (*lineptr == NULL)
			return (-1);
		*n = INITIAL_LINE_SIZE;
	}
	return (0);
}
/* betty style doc for function mem_realloc goes there */
/**
 * mem_realloc - Entry point
 * @lc: first arg
 * @ls: second arg
 * @line: third arg
 * @lineptr: fourth arg
 * @n: fifth arg
 * Return: int
 */
int mem_realloc(size_t lc, size_t ls, char *line, char **lineptr, size_t *n)
{
	char *new_line;
	size_t new_capacity, i;

	new_capacity = lc * 2;
	new_line = malloc(new_capacity);
	if (new_line == NULL)
		return (-1);
	for (i = 0; i < ls; i++)
	{
		new_line[i] = line[i];
	}
	free(line);
	line = new_line;
	*lineptr = line;
	lc = new_capacity;
	*n = lc;
	return (0);
}

/* betty style doc for function _getline goes there */
/**
 * _getline - Entry point
 * @lineptr: first arg
 * @n: second arg
 * @fd: third arg
 * Return: ssize_t
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[BUFFER_SIZE];
	static int buffer_pos;
	static int buffer_size;
	char *line = NULL, c;
	size_t line_size = 0, line_capacity = 0, chars_read = 0;
	int result;

	buffer_pos = 0;
	buffer_size = 0;
	if (check_input(lineptr, n) == -1)
		return (-1);
	line = *lineptr;
	line_capacity = *n;
	while (1)
	{
		if (buffer_pos >= buffer_size)
		{
			buffer_size = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_size <= 0)
			{
				if (chars_read == 0)
					return (-1);
				break;
			}
		}
		c = buffer[buffer_pos++];
		chars_read++;
		if (line_size + 1 >= line_capacity)
		{
			result = mem_realloc(line_capacity, line_size, line, lineptr, n);
			if (result == -1)
				return (-1);
		}
		line[line_size++] = c;
		if (c == '\n')
			break;
	}
	line[line_size] = '\0';
	return (chars_read);
}

