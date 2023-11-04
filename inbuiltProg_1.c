#include "BlessBenShell.h"

/**
 * _myhistory - This func simply displays the history list
 * @bensInfo: This is the structure that contains future arguments
 *  Return: 0(Always)
 */

int _myhistory(info_t *bensInfo)
{
	print_list(bensInfo->history);
	return (0);
}

/**
 * unset_alias - This func simply sets
 * alias to string in our prog
 * @bensInfo: This is the parameter
 * struct in our prog
 * @str: This is the string
 * alias of our prog
 * Return: 0(SUCCESS), else 1(ERROR)
 */

int unset_alias(info_t *bensInfo, char *str)
{
	int ret;
	char *point, c;

	point = _strchr(str, '=');
	if (!point)
	{
		return (1);
	}
	c = *point;
	*point = 0;
	ret = delete_node_at_index(&(bensInfo->alias),
		get_node_index(bensInfo->alias, node_starts_with(bensInfo->alias, str, -1)));
	*point = c;
	return (ret);
}

/**
 * set_alias - This func will set
 * alias to string in our prog
 *
 * @bensInfo: This is the parameter struct in our prog
 *
 * @str: This is the string alias of our prog
 *
 * Return: 0(SUCCESS), else 1(ERROR)
 *
 */
int set_alias(info_t *bensInfo, char *str)
{
	char *point;

	point = _strchr(str, '=');
	if (!point)
	{
		return (1);
	}
	if (!*++point)
	{
		return (unset_alias(bensInfo, str));
	}

	unset_alias(bensInfo, str);
	return (add_node_end(&(bensInfo->alias), str, 0) == NULL);
}

/**
 * print_alias - This func simply prints
 * an alias string in our prog
 *
 * @node: The programs node
 *
 * Return: 0(SUCCESS), else 1(ERROR)
 *
 */

int print_alias(list_t *node)
{
	char *point = NULL, *w = NULL;

	if (node)
	{
		point = _strchr(node->str, '=');
		for (w = node->str; w <= point; w++)
			_putchar(*w);
		_putchar('\'');
		_puts(point + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - This func simply behaves like
 * the alias builtin (compare man alias)
 *
 * @bensInfo: This is the structure that contains future arguments
 *
 *  Return: 0(ALWAYS)
 *
 */

int _myalias(info_t *bensInfo)
{
	int k = 0;
	list_t *node = NULL;
	char *point = NULL;

	if (bensInfo->argc == 1)
	{
		node = bensInfo->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (k = 1; bensInfo->argv[k]; k++)
	{
		point = _strchr(bensInfo->argv[k], '=');
		if (point)
		{
			set_alias(bensInfo, bensInfo->argv[k]);
		}
		else
		{
			print_alias(node_starts_with(bensInfo->alias, bensInfo->argv[k], '='));
		}
	}

	return (0);
}
