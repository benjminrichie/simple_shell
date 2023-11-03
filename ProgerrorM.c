#include "BlessBenShell.h"

/**
 * put_myfd - This func simply writes char
 * @c: This is the char
 * @fd: This is the filedescriptor
 * Return: 1(SUCCESS)
 */

int put_myfd(char c, int fd)
{
	static char blessbuf[WRITE_BUF_SIZE];
	static int k;

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, blessbuf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
	{
		blessbuf[k++] = c;
	}
	return (1);
}

/**
 *put_myfd - This func simply prints inputs
 * @str: This is the string input
 * @fd: This represents the filedescriptor
 * Return: The chars
 */

int puts_myfd(char *str, int fd)
{
	int k = 0;

	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		k += put_myfd(*str++, fd);
	}
	return (k);
}

/**
 *_eputs -This func will print inputs in our prog
 * @str: This is the input string of our prog
 * Return: void
 */

void _eputs(char *str)
{
	int k = 0;

	if (!str)
	{
		return;
	}
	while (str[k] != '\0')
	{
		_eputchar(str[k]);
		k++;
	}
}

/**
 * _eputchar - This func simply writes char
 * @c: This is the char to be written to sdterr
 * Return: 1(SUCCESS)
 */

int _eputchar(char c)
{
	static char blessbuf[WRITE_BUF_SIZE];
	static int k;

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, blessbuf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
	{
		blessbuf[k++] = c;
	}

	return (1);
}
