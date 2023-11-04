#include "BlessBenShell.h"

/**
 **_memset - This func will fill memory
 *@s: Just a pointer
 *@b: This is the byte that pointer *s will fill
 *@n: This is the number of bytes the prog is to fill
 *Return: A pointer
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int k;

	for (k = 0; k < n; k++)
		s[k] = b;
	return (s);
}

/**
 * ffree - This func simply frees a string
 * @pp: This is the str of str in our prog
 */

void ffree(char **pp)
{
	char **w = pp;

	if (!pp)
	{
		return;
	}
	while (*pp)
	{
		free(*pp++);
	}
	free(w);
}

/**
 * _realloc - This func will just
 * reallocate mem
 * @ptr: Just a pointer
 * @old_size: This is the prev byte size
 * @new_size: This is the new byte size
 * Return: A pointer
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *point;

	if (!ptr)
	{
		return (malloc(new_size));
	}
	if (!new_size)
	{
		return (free(ptr), NULL);
	}
	if (new_size == old_size)
	{
		return (ptr);
	}

	point = malloc(new_size);
	if (!point)
	{
		return (NULL);
	}

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	{
		point[old_size] = ((char *)ptr)[old_size];
	}
	free(ptr);

	return (point);
}
