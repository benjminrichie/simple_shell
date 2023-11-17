#include "myShellHeader.h"

/**
 * _myenv - This will print the current environment in this prog
 *
 * @info: This is the structure that contains arguments
 *
 * Return: 0(Always)
 *
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	{
	return (0);
	}
}

/**
 * _getenv - This func will get the value of
 * an environ variable in this prog
 *
 * @info: This is the structure that contains arguments
 *
 * @name: This is the name
 *
 * Return: value
 *
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
		{
			return (p);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - This func will either Initialize a new
 * environment variable or will just simply modify an existing one
 *
 * @info: This is the structure that contains arguments
 *
 *  Return: 0(Always)
 *
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _myunsetenv - This func will remove an environment variable in ur prog
 *
 * @info: This is the structure that containin arguments
 *
 *  Return: 0(Always)
 *
 */

int _myunsetenv(info_t *info)
{
	int f;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (f = 1; f <= info->argc; f++)
		_unsetenv(info, info->argv[f]);

	return (0);
}

/**
 * populate_env_list - This func populates
 * env linked list in this prog
 *
 * @info: This is the structure that contains arguments
 *
 * Return: 0(Always)
 *
 */

int populate_env_list(info_t *info)
{
	size_t f;
	list_t *node = NULL;

	for (f = 0; environ[f]; f++)
	{
		add_node_end(&node, environ[f], 0);
	}
	info->env = node;
	return (0);
}
