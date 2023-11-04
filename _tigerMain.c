#include "BlessBenShell.h"

/**
 * main - This will be our entry point for this func
 *
 * @ac: To represent arg count in our prog
 *
 * @av: To represent arg vector in our prog
 *
 * Return: 0(success), else 1(error)
 */

int main(int ac, char **av)
{
	int fd = 2;
	info_t bensInfo[] = { INFO_INIT };

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
			{
				exit(126);
			}
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		bensInfo->readfd = fd;
	}
	populate_env_list(bensInfo);
	read_history(bensInfo);
	hsh(bensInfo, av);
	return (EXIT_SUCCESS);
}
