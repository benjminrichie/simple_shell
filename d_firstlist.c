#include "BlessBenShell.h"

/**
 * list_len - This func will just determine the
 * length of linked list in our prog
 *
 * @h: This is a pointer
 *
 * Return: size
 */

size_t list_len(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * list_to_strings - This func will return an array of strings
 *
 * @head: Just a pointer
 *
 * Return: array of strings
 *
 */

char **list_to_strings(list_t *head)
{
	char **strs;
	char *str;
	list_t *node = head;
	size_t k = list_len(head), l;

	if (!head || !k)
	{
		return (NULL);
	}
	strs = malloc(sizeof(char *) * (k + 1));
	if (!strs)
	{
		return (NULL);
	}
	for (k = 0; node; node = node->next, k++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (l = 0; l < k; l++)
			{
				free(strs[l]);
			}
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[k] = str;
	}
	strs[k] = NULL;
	return (strs);
}


/**
 * print_list - Thid func simply prints elements
 * of a list_t linked list in our program
 *
 * @h: Just a pointer
 *
 * Return: size
 *
 */

size_t print_list(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * node_starts_with - This func simply returns node
 * whose string starts with prefixin our prog
 *
 * @node: just a pointer
 *
 * @prefix: This is the string to match in our prog
 *
 * @c: This is the next char
 *
 * Return: simply return node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *point = NULL;

	while (node)
	{
		point = starts_with(node->str, prefix);
		if (point && ((c == -1) || (*point == c)))
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - This is the func that
 * gets the index of a node in our prog
 *
 * @head: Just a pointer to the very first node
 *
 * @node: Just a pointer to the node in our prog
 *
 * Return: Just returns index or -1
 *
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
		{
			return (k);
		}
		head = head->next;
		k++;
	}
	return (-1);
}
