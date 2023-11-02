#include "BlessBenShell.h"

/**
 **_strchr - This simply locates a char in our prog
 *@Dstring: This is the string
 *@c: This is the char
 *Return: pointer(Dstring)
 */

char *_strchr(char *Dstring, char c)
{
	do {
		if (*Dstring == c)
		{
			return (Dstring);
		}
	} while (*Dstring++ != '\0');

	return (NULL);
}

/**
 **_strncpy - This func will just copy a string in this prog
 *@dest: This is the destination copy to
 *@src: This is the source to copy from
 *@n: This is the amount of characters we are to simply copy
 *Return: string
 */

char *_strncpy(char *dest, char *src, int n)
{
	char *Dstring = dest;
	int k, l;

	k = 0;
	while (src[k] != '\0' && k < n - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < n)
	{
		l = k;
		while (l < n)
		{
			dest[l] = '\0';
			l++;
		}
	}
	return (Dstring);
}

/**
 **_strncat - This Func will concatenate two strings in our prog
 *@dest: this is string 1 in our prog
 *@src: this is string 2 in our prog
 *@n: This is the amount of bytes to use atmost
 *Return: string
 */

char *_strncat(char *dest, char *src, int n)
{
	int k, l;
	char *Dstring = dest;

	k = 0;
	l = 0;
	while (dest[k] != '\0')
	{
		k++;
	}
	while (src[l] != '\0' && l < n)
	{
		dest[k] = src[l];
		k++;
		l++;
	}
	if (l < n)
		dest[k] = '\0';
	return (Dstring);
}
