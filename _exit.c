#include "shell.h"

/**
 **_strncpy - This func will copy a string in our prog
 *@dest: This is the destination
 *@src: This is the source to copy from
 *@n: This is the amount of chars to copy
 *Return: string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int f, g;
	char *s = dest;

	f = 0;
	while (src[f] != '\0' && f < n - 1)
	{
		dest[f] = src[f];
		f++;
	}
	if (f < n)
	{
		g = f;
		while (g < n)
		{
			dest[g] = '\0';
			g++;
		}
	}
	return (s);
}

/**
 **_strncat - This func will concatenat two strings in our prog
 *@dest: This is str1
 *@src: This is str2
 *@n: This is the number of bytes to be used maximally
 *Return: string
 */

char *_strncat(char *dest, char *src, int n)
{
	int f, g;
	char *s = dest;

	f = 0;
	g = 0;
	while (dest[f] != '\0')
	{
		f++;
	}
	while (src[g] != '\0' && g < n)
	{
		dest[f] = src[g];
		f++;
		g++;
	}
	if (g < n)
	{
		dest[f] = '\0';
	}
	return (s);
}

/**
 **_strchr - This func simply locates a char in a string
 *@s: This is the str
 *@c: This is the char to look for
 *Return: A pointer
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ != '\0');

	return (NULL);
}
