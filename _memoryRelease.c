#include "BlessBenShell.h"

/**
 * freetiger - This func will simply
 * free a ptr and sets the address to NULL
 *
 * @ptr: address of the pointer to free
 *
 * Return: 1(FREED), else 0.
 */

int freetiger(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
