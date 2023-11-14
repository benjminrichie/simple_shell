#include "myShellHeader.h"

/**
 * add_node - This func will add a node
 * to the start of the list in this program.
 *
 * @head: This is the first node.
 *
 * @str: string.
 *
 * @num: number.
 *
 * Return: size.
 *
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
	{
		return (NULL);
	}
	new_head = malloc(sizeof(list_t));
	if (!new_head)
	{
		return (NULL);
	}
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - This func will add a node
 * to the end of the list in our program.
 *
 * @head: This is the fist node.
 *
 * @str: string.
 *
 * @num: number.
 *
 * Return: size.
 *
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
	{
		return (NULL);
	}
	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
	{
		return (NULL);
	}
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
		{
			node = node->next;
		}
		node->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}

/**
 * print_list_str - This func will only print
 * the string element of a list_t linked list.
 *
 * @h: This is the first node.
 *
 * Return: size.
 *
 */

size_t print_list_str(const list_t *h)
{
	size_t f = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		f++;
	}
	return (f);
}

/**
 * delete_node_at_index - This is the func that will
 * delete a node at a given index in our program
 *
 * @head: This is the very first node.
 *
 * @index: index to be deleted.
 *
 * Return: 1(SUCCESS), else 0(FAILURE).
 *
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	unsigned int f = 0;
	list_t *node, *prev_node;

	if (!head || !*head)
	{
		return (0);
	}

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (f == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		f++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - This func simply frees all
 * nodes of a list in our program.
 *
 * @head_ptr: The very first node.
 *
 * Return: void.
 *
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
	{
		return;
	}
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
