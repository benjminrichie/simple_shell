#include "shell.h"

/**
 * bfree - This is the function that is responsible for
 * freeing a pointer and sets the address to NULL
 *
 * @ptr: Just a pointer
 *
 * Return: 1(FREED), else 0.
 *
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
