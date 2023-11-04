#include "shell.h"

/**
 * get_environ - This func will only return the
 * string array copy of our environ for this prog
 *
 * @info: This is the structure that  contains arguments
 *
 * Return: 0(Always)
 *
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - This func will remove an
 * environment variable in our prog
 *
 * @info: This is the structure that contains arguments
 *
 * @var: This is the string env var property od our prog
 *
 *  Return: 1(DELETE)
 *
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	char *p;
	size_t f = 0;

	if (!node || !var)
	{
		return (0);
	}

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), f);
			f = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		f++;
	}
	return (info->env_changed);
}

/**
 * _setenv - This is the func that will initialize a new
 * environment variable or modify an existing one in our program
 *
 * @info: This is the structure that containins arguments
 *
 * @var: This is the string env var property of our func
 *
 * @value: str value
 *
 *  Return: 0(Always)
 *
 */

int _setenv(info_t *info, char *var, char *value)
{
	list_t *node;
	char *p;
	char *buf = NULL;

	if (!var || !value)
	{
		return (0);
	}

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
	{
		return (1);
	}
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

