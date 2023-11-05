#include "shell.h"

/**
 * _strlen - This is the func that returns the
 * length of a string in our prog
 *
 * @s: This is the str
 *
 * Return: integer
 *
 */

int _strlen(char *s)
{
	int f = 0;

	if (!s)
	{
		return (0);
	}

	while (*s++)
	{
		f++;
	}
	return (f);
}

/**
 * _strcmp - This function performs
 * lexicogarphic comparism of two strings in this prog
 *
 * @s1: string 1
 *
 * @s2: string 2
 *
 * Return: s1 < s2(NEGATIVE), else s1 > s2(POSITIVE),
 * else s1 == s2(ZERO)
 *
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	if (*s1 == *s2)
	{
		return (0);
	}
	else
	{
		return (*s1 < *s2 ? -1 : 1);
	}
}

/**
 * starts_with - This func only checks if needle
 * starts with haystack in this prog
 *
 * @haystack: This is the string to search for
 *
 * @needle: This is the substring to find in the prog
 *
 * Return: A pointer or NULL
 *
 */

char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
	{
		if (*needle++ != *haystack++)
		{
			return (NULL);
		}
	}
	return ((char *)haystack);
}

/**
 * _strcat - This func only
 * concatenates two strings in this prog
 *
 * @dest: This is the destination
 *
 * @src: This is the source
 *
 * Return: Just a pointer
 *
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = *src;
	return (ret);
}
