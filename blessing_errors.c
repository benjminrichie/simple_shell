#include "shell.h"

/**
 *_eputs - This func will only print strings in our prog
 * @str: This is the string
 *
 * Return: Void
 *
 */

void _eputs(char *str)
{
	int f = 0;

	if (!str)
	{
		return;
	}
	while (str[f] != '\0')
	{
		_eputchar(str[f]);
		f++;
	}
}

/**
 * _eputchar - Ths func is responsible for
 * writing Char c to stderr in our prog
 *
 * @c: This is the char
 *
 * Return: 1 (SUCCESS), else -1 (ERROR)
 *
 */

int _eputchar(char c)
{
	static int f;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || f >= WRITE_BUF_SIZE)
	{
		write(2, buf, f);
		f = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[f++] = c;
	}
	return (1);
}

/**
 * _putfd - THis func will only write
 * char c to the given fd in our prog
 *
 * @c: This is the char
 *
 * @fd: This represents the filedescriptor
 * we are writing to in this prog
 *
 * Return: 1(SUCCESS), else -1(ERROR)
 *
 */

int _putfd(char c, int fd)
{
	static int f;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || f >= WRITE_BUF_SIZE)
	{
		write(fd, buf, f);
		f = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[f++] = c;
	}
	return (1);
}

/**
 *_putsfd - This func is just to print input str in our prog
 * @str: This is the string
 *
 * @fd: This represents the filedescriptor
 * that we are writing to in our prog
 *
 * Return: char
 *
 */

int _putsfd(char *str, int fd)
{
	int f = 0;

	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		f += _putfd(*str++, fd);
	}
	return (f);
}
