#include "BlessBenShell.h"

/**
 * setmy_environt - This funct simply initialize a new
 * env var in our prog or modifies previous
 * @bensInfo: This is the structure that
 * contains future arguments in our prog
 * @var: Representing string
 * @value: a value
 *  Return: 0(ALWAYS)
 */

int setmy_environt(info_t *bensInfo, char *var, char *value)
{
	char *myP;
	char *blessbuf = NULL;
	list_t *node;

	if (!var || !value)
	{
		return (0);
	}
	blessbuf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!blessbuf)
	{
		return (1);
	}
	_strcpy(blessbuf, var);
	_strcat(blessbuf, "=");
	_strcat(blessbuf, value);
	node = bensInfo->env;
	while (node)
	{
		myP = starts_with(node->str, var);
		if (myP && *myP == '=')
		{
			free(node->str);
			node->str = blessbuf;
			bensInfo->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(bensInfo->env), blessbuf, 0);
	free(blessbuf);
	bensInfo->env_changed = 1;
	return (0);
}

/**
 * di_setmyenviron - This func will remove an
 * environment variable in our prog
 * @bensInfo: This Struct will contain future arguments
 *  Return: 1(DELETE), else 0
 * @var: Just astring
 */

int di_setmyenviron(info_t *bensInfo, char *var)
{
	list_t *node = bensInfo->env;
	size_t k = 0;
	char *myP;

	if (!node || !var)
	{
		return (0);
	}

	while (node)
	{
		myP = starts_with(node->str, var);
		if (myP && *myP == '=')
		{
			bensInfo->env_changed = delete_node_at_index(&(bensInfo->env), k);
			k = 0;
			node = bensInfo->env;
			continue;
		}
		node = node->next;
		k++;
	}
	return (bensInfo->env_changed);
}

/**
 * _environFuncT - This func will return a
 * string array in our prog
 * @bensInfo: this is the struct that
 * contains future arguments in our prog
 * Return: 0(Always)
 */

char **_environFuncT(info_t *bensInfo)
{
	if (!bensInfo->environ || bensInfo->env_changed)
	{
		bensInfo->environ = list_to_strings(bensInfo->env);
		bensInfo->env_changed = 0;
	}

	return (bensInfo->environ);
}
