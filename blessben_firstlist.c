#include "shell.h"

/**
 * list_len - This function will just determine
 * the  length of a linked list in our prog
 *
 * @h: pointer to the very first node
 *
 * Return: size
 *
 */

size_t list_len(const list_t *h)
{
	size_t f = 0;

	while (h)
	{
		h = h->next;
		f++;
	}
	return (f);
}

/**
 * list_to_strings - This function simply returns an array of strings
 *
 * @head: just a pointer to the very first node
 *
 * Return: only an array of strings for the prog
 *
 */

char **list_to_strings(list_t *head)
{
	char *str;
	char **strs;
	size_t f = list_len(head), g;
	list_t *node = head;

	if (!head || !f)
	{
		return (NULL);
	}
	strs = malloc(sizeof(char *) * (f + 1));
	if (!strs)
	{
		return (NULL);
	}
	for (f = 0; node; node = node->next, f++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (g = 0; g < f; g++)
			{
				free(strs[g]);
			}
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[f] = str;
	}
	strs[f] = NULL;
	return (strs);
}


/**
 * print_list - This function will just print the
 * elements of a list_t linked list in this prog
 *
 * @h: Just a pointer to the very first node
 *
 * Return: size
 *
 */

size_t print_list(const list_t *h)
{
	size_t f = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		f++;
	}
	return (f);
}

/**
 * node_starts_with - This function simply returns
 * the node whose string starts with a prefix
 *
 * @node: Just a pointer to the very first node
 *
 * @prefix: This is the string to match in this prog
 *
 * @c: char
 *
 * Return: A node or null
 *
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
		{
			return (node);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - This func simply gets
 * the index of a node in this prog
 *
 * @head: This is a pointer
 *
 * @node: Another pointer
 *
 * Return: Just the index of a node or -1
 *
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t f = 0;

	while (head)
	{
		if (head == node)
		{
			return (f);
		}
		head = head->next;
		f++;
	}
	return (-1);
}
