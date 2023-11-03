#include "BlessBenShell.h"

/**
 * _tostart - This will check if needle starts with haystack
 * @haystack: Represents the string
 * @needle: Represents the substring
 * Return: A pointer or NULL
 */

char *_tostart(const char *haystack, const char *needle)
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
 * _strlen - This func will return
 * length of string in our prog
 * @s: This is the string
 * Return: int
 */

int _strlen(char *s)
{
	int k = 0;

	if (!s)
	{
		return (0);
	}
	while (*s++)
	{
		k++;
	}

	return (k);
}

/**
 * _strcat - This fun will concatenate strings in our prog
 * @dest: end point
 * @src: starting point in our prog
 * Return: Just a pointer
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

/**
 * _strcmp - This func compares two strangs.
 *
 * @s1: str 1
 *
 * @s2: str 2
 *
 * Return: if s1 < s2(NEGATIVE),
 * else if s1 > s2(POSITIVE),
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
