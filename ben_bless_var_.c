#include "BlessBenShell.h"

/**
 * _checkmychainP - This func simply checks if we should continue
 *
 * @bensInfo: This is the parameter struct of our prog
 *
 * @blessbuf: This is the character buffer of our prog
 *
 * @point: Just a pointer
 *
 * @k: This is the starting position in buf initialized
 *
 * @len: This represents length
 *
 * Return: Nothing
 *
 */

void _checkmychainP(info_t *bensInfo, char *blessbuf,
		size_t *point, size_t k, size_t len)
{
	size_t l = *point;

	if (bensInfo->cmd_buf_type == CMD_AND)
	{
		if (bensInfo->status)
		{
			blessbuf[k] = 0;
			l = len;
		}
	}
	if (bensInfo->cmd_buf_type == CMD_OR)
	{
		if (!bensInfo->status)
		{
			blessbuf[k] = 0;
			l = len;
		}
	}

	*point = l;
}

/**
 * _chainme - This func will test current char
 * in buffer to see if its a delimeter or not
 *
 * @bensInfo: This is the parameter struct of our prog
 *
 * @blessbuf: This is the character buffer of the prog
 *
 * @point: Just pointer
 *
 * Return: 1(delimeter), else 0
 *
 */

int _chainme(info_t *bensInfo, char *blessbuf, size_t *point)
{
	size_t l = *point;

	if (blessbuf[l] == '|' && blessbuf[l + 1] == '|')
	{
		blessbuf[l] = 0;
		l++;
		bensInfo->cmd_buf_type = CMD_OR;
	}
	else if (blessbuf[l] == '&' && blessbuf[l + 1] == '&')
	{
		blessbuf[l] = 0;
		l++;
		bensInfo->cmd_buf_type = CMD_AND;
	}
	else if (blessbuf[l] == ';')
	{
		blessbuf[l] = 0;
		bensInfo->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*point = l;
	return (1);
}

/**
 * Tigreplace_var - This func will replace a var in the nicetoke string
 *
 * @bensInfo: This is the parameter struct of our prog
 *
 * Return: 1(REPLACED), else 0
 *
 */

int Tigreplace_var(info_t *bensInfo)
{
	list_t *node;
	int k = 0;

	for (k = 0; bensInfo->argv[k]; k++)
	{
		if (bensInfo->argv[k][0] != '$' || !bensInfo->argv[k][1])
			continue;

		if (!_strcmp(bensInfo->argv[k], "$?"))
		{
			Tigreplace_var(&(bensInfo->argv[k]),
				_strdup(convert_number(bensInfo->status, 10, 0)));
			continue;
		}
		if (!_strcmp(bensInfo->argv[k], "$$"))
		{
			Tigreplace_var(&(bensInfo->argv[k]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(bensInfo->env, &bensInfo->argv[k][1], '=');
		if (node)
		{
			Tigreplace_var(&(bensInfo->argv[k]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		Tigreplace_var(&bensInfo->argv[k], _strdup(""));

	}
	return (0);
}

/**
 * _stringreplacement_ - This func simply replaces a string in our prog
 *
 * @old: This is the old address
 *
 * @new: This is the new string address
 *
 * Return: 1 (REPLACED), else 0
 *
 */

int _stringreplacement_(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * replace_alias - This func will replace an alias in the nicetoken
 *
 * @bensInfo: This is the parameter struct of our prog
 *
 * Return: 1 (REPLACED), else 0
 *
 */

int replace_alias(info_t *bensInfo)
{
	char *point;
	int k;
	list_t *node;

	for (k = 0; k < 10; k++)
	{
		node = node_starts_with(bensInfo->alias, bensInfo->argv[0], '=');
		if (!node)
		{
			return (0);
		}
		free(bensInfo->argv[0]);
		point = _strchr(node->str, '=');
		if (!point)
		{
			return (0);
		}
		point = _strdup(point + 1);
		if (!point)
		{
			return (0);
		}
		bensInfo->argv[0] = point;
	}
	return (1);
}
