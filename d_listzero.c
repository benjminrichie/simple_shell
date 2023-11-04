#include "BlessBenShell.h"

/**
 * add_node_end - This func will add a
 * node to the end of the list in our prog
 *
 * @head: Justg a pointer to the first node or item
 *
 * @str: The string
 *
 * @num: The node index in the prog
 *
 * Return: size
 *
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *MyNewNodeMe, *node;

	if (!head)
	{
		return (NULL);
	}

	node = *head;
	MyNewNodeMe = malloc(sizeof(list_t));
	if (!MyNewNodeMe)
	{
		return (NULL);
	}
	_memset((void *)MyNewNodeMe, 0, sizeof(list_t));
	MyNewNodeMe->num = num;
	if (str)
	{
		MyNewNodeMe->str = _strdup(str);
		if (!MyNewNodeMe->str)
		{
			free(MyNewNodeMe);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = MyNewNodeMe;
	}
	else
	{
		*head = MyNewNodeMe;
	}
	return (MyNewNodeMe);
}

/**
 * free_list - This fun c will just free all
 * nodes of a list in our prog
 *
 * @head_ptr: just a pointer to the first item
 *
 * Return: Nothing
 *
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *MyNextNodeMe, *head;

	if (!head_ptr || !*head_ptr)
	{
		return;
	}
	head = *head_ptr;
	node = head;

	while (node)
	{
		MyNextNodeMe = node->next;
		free(node->str);
		free(node);
		node = MyNextNodeMe;
	}
	*head_ptr = NULL;
}

/**
 * print_list_str - This func will print
 * the string element of inked list in our prog
 *
 * @h: Just a pointer to the very first
 * node representing the head
 *
 * Return: size
 *
 */

size_t print_list_str(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * add_node - This func will add
 * a node to the list in our prog
 *
 * @head: This is a pointer to the first item in the list
 *
 * @str: The string
 *
 * @num: This is the node index
 *
 * Return: size
 *
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *MynewHeadMe;

	if (!head)
	{
		return (NULL);
	}
	MynewHeadMe = malloc(sizeof(list_t));
	if (!MynewHeadMe)
	{
		return (NULL);
	}
	_memset((void *)MynewHeadMe, 0, sizeof(list_t));
	MynewHeadMe->num = num;
	if (str)
	{
		MynewHeadMe->str = _strdup(str);
		if (!MynewHeadMe->str)
		{
			free(MynewHeadMe);
			return (NULL);
		}
	}
	MynewHeadMe->next = *head;
	*head = MynewHeadMe;
	return (MynewHeadMe);
}

/**
 * delete_node_at_index - This fun will delete
 * the nodes at an index provided or specified
 *
 * @head: Just a pointer to first node in our prog
 *
 * @index: index to delete in the prog
 *
 * Return: 1(SUCCESS), else 0(FAIL)
 *
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	unsigned int k = 0;
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
		if (k == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		k++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
