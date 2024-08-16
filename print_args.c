#include <unistd.h>
/* betty style doc for function _sqrt_check goes there */
/**
 * main - Entry point
 * @ac: first arg
 * @av: second arg
 *
 * Return: Always return 0
 */
int main(int ac, char **av)
{
	int i = 0, j = 0;
	char nl = '\n';

	if (ac > 0)
	{
		while (*(av + i))
		{
			j = 0;
			while (*(av[i] + j))
			{
				write(1, &av[i][j], 1);
				j++;
			}
			write(1, &nl, 1);
			i++;
		}
	}

	return (0);
}
