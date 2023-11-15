#include "myShellHeader.h"

/**
 **_memset - This func simply fills the memory with a constant byte in our prog
 *@s: Just a pointer
 *@b: This is the byte to fill
 *@n: Represents the amount of bytes
 *Return: Just a pointer
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int f;

	for (f = 0; f < n; f++)
	{
		s[f] = b;
	}
	return (s);
}

/**
 * ffree - This func will only free a string
 * of strings in our prog
 *
 * @pp: This is the str of str in our prog
 *
 */

void ffree(char **pp)
{
	char **z = pp;

	if (!pp)
	{
		return;
	}
	while (*pp)
	{
		free(*pp++);
	}
	free(z);
}

/**
 * _realloc - This is the function that will
 * reallocate a block of memory in our program
 *
 * @ptr: just a pointer
 *
 * @old_size: This is the old byte size
 *
 * @new_size: This is the new byte size
 *
 * Return: A pointer
 *
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

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
	p = malloc(new_size);
	if (!p)
	{
		return (NULL);
	}
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	{
		p[old_size] = ((char *)ptr)[old_size];
	}
	free(ptr);
	return (p);
}
