#include "BlessBenShell.h"

/**
 * _myenv - This func will just print the present env in our prog
 * @bensInfo: This is the structure that contains future arguments
 * Return: 0 (Always)
 */

int _myenv(info_t *bensInfo)
{
	print_list_str(bensInfo->env);
	return (0);
}

/**
 * _getenv - This func gets the
 * value of environ variable in the prog
 * @bensInfo: This is the structure that contains future arguments
 * @name: This is the env variable name
 * Return: A value
 */

char *_getenv(info_t *bensInfo, const char *name)
{
	char *point;
	list_t *node = bensInfo->env;

	while (node)
	{
		point = starts_with(node->str, name);
		if (point && *point)
		{
			return (point);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - This is the func that initialize a
 * new env variable in our prog
 * @bensInfo: This is the structure that contains future arguments
 * Return: 0 (Always)
 */

int _mysetenv(info_t *bensInfo)
{
	if (bensInfo->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (setmy_environt(bensInfo, bensInfo->argv[1], bensInfo->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _myunsetenv - This func will remove an env var in this prog
 * @bensInfo: This is the structure that contains future arguments
 *  Return: 0(Always)
 */

int _myunsetenv(info_t *bensInfo)
{
	int k;

	if (bensInfo->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= bensInfo->argc; k++)
	{
		di_setmyenviron(bensInfo, bensInfo->argv[k]);
	}

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @bensInfo: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *bensInfo)
{
	size_t k;
	list_t *node = NULL;

	for (k = 0; environ[k]; k++)
	{
		add_node_end(&node, environ[k], 0);
	}
	bensInfo->env = node;
	return (0);
}
