#include "BlessBenShell.h"

/**
 *_puts - This will print input in our program
 *@str: This is the string in our prog
 * Return: void(Nothing)
 */

void _puts(char *str)
{
	int k = 0;

	if (!str)
	{
		return;
	}
	while (str[k] != '\0')
	{
		_putchar(str[k]);
		k++;
	}
}

/**
 * _strcpy - This func simply copy strings in our prog
 * @dest: end point
 * @src: strting point
 * Return: A pointer
 */

char *_strcpy(char *dest, char *src)
{
	int k = 0;

	if (dest == src || src == 0)
	{
		return (dest);
	}
	while (src[k])
	{
		dest[k] = src[k];
		k++;
	}
	dest[k] = 0;
	return (dest);
}

/**
 * _strdup - This will duplicate strings in our prog
 * @str: This reprsents the string in our prog
 * Return: A pointer
 */

char *_strdup(const char *str)
{
	char *returnMe;
	int length = 0;

	if (str == NULL)
	{
		return (NULL);
	}
	while (*str++)
	{
		length++;
	}
	returnMe = malloc(sizeof(char) * (length + 1));
	if (!returnMe)
	{
		return (NULL);
	}
	for (length++; length--;)
	{
		returnMe[length] = *--str;
	}

	return (returnMe);
}

/**
 * _putchar - This func will only write char in our prog
 * @c: This is the char ro be written to stdout of our prog
 * Return: 1(SUCCESS) else -1(ERROR)
 */

int _putchar(char c)
{
	static int k;
	static char blessbuf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(1, blessbuf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		blessbuf[k++] = c;
	return (1);
}
