#include "myShellHeader.h"

/**
 * _strcpy - This func simply copies a string in this prog
 *
 * @dest: This is the destination we are copying to
 *
 * @src: This is the source we are copying from
 *
 * Return: A pointer that points to dest
 *
 */

char *_strcpy(char *dest, char *src)
{
	int f = 0;

	if (dest == src || src == 0)
	{
		return (dest);
	}
	while (src[f])
	{
		dest[f] = src[f];
		f++;
	}
	dest[f] = 0;
	return (dest);
}

/**
 * _strdup - This func only duplicates a string in this prog
 *
 * @str: This is the string
 *
 * Return: A pointed that point to the operation carried out
 *
 */

char *_strdup(const char *str)
{
	char *ret;
	int length = 0;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*str++)
	{
		length++;
	}
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
	{
		return (NULL);
	}
	for (length++; length--;)
	{
		ret[length] = *--str;
	}
	return (ret);
}

/**
 *_puts - This function will only print an input string in this program
 *@str: This is the string of interest
 * Return: Nothing
 */

void _puts(char *str)
{
	int f = 0;

	if (!str)
	{
		return;
	}
	while (str[f] != '\0')
	{
		_putchar(str[f]);
		f++;
	}
}

/**
 * _putchar - This func will write char c to stdout in our prog
 *
 * @c: This is the char
 *
 * Return: 1(SUCCESS) else -1(ERROR)
 *
 */

int _putchar(char c)
{
	static char buf[WRITE_BUF_SIZE];
	static int f;

	if (c == BUF_FLUSH || f >= WRITE_BUF_SIZE)
	{
		write(1, buf, f);
		f = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[f++] = c;
	}
	return (1);
}
