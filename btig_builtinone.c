#include "myShellHeader.h"

/**
 * _myhistory - This func will display the history list
 *
 * @info: This is the structure that contains arguments
 *
 * Return: 0(Always)
 *
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	{
	return (0);
	}
}

/**
 * unset_alias - This will unset alias to string in our prog
 *
 * @info: This is the parameter struct in our prog
 *
 * @str: This is the string
 *
 * Return: 0 (success), else 1 (error)
 *
 */

int unset_alias(info_t *info, char *str)
{
	char *p, w;
	int ret;

	p = _strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	w = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = w;
	return (ret);
}

/**
 * set_alias - This func will set alias to string in our prog
 *
 * @info: This is the parameter struct in our prog
 *
 * @str: This is the string
 *
 * Return: 0 (success), else 1 (error)
 *
 */

int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
	{
		return (1);
	}
	if (!*++p)
	{
		return (unset_alias(info, str));
	}

	unset_alias(info, str);
	{
	return (add_node_end(&(info->alias), str, 0) == NULL);
	}
}

/**
 * print_alias - This func will just
 * print an alias string in our prog
 *
 * @node: this will reppresent the
 * alias node in our prog
 *
 * Return: 0 (success), else 1 (error)
 *
 */

int print_alias(list_t *node)
{
	char *p = NULL, *z = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (z = node->str; z <= p; z++)
			_putchar(*z);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - This func will only do as(mimic) the
 * alias builtin (man alias) in our prog
 *
 * @info: This is the structure that contains arguments
 *
 *  Return: 0 (Always)
 *
 */

int _myalias(info_t *info)
{
	char *p = NULL;
	int f = 0;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (f = 1; info->argv[f]; f++)
	{
		p = _strchr(info->argv[f], '=');
		if (p)
			set_alias(info, info->argv[f]);
		else
			print_alias(node_starts_with(info->alias, info->argv[f], '='));
	}

	return (0);
}
