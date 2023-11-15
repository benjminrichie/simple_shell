#include "myShellHeader.h"

/**
 * is_chain - This func will only test if current char
 * in buffer is a chain delimeter in our prog
 *
 * @info: This is the parameter struct of our prog
 *
 * @buf: This is the character buffer of our prog
 *
 * @p: just a pointer
 *
 * Return: 1(chain delimeter), else 0
 *
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t g = *p;

	if (buf[g] == '|' && buf[g + 1] == '|')
	{
		buf[g] = 0;
		g++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[g] == '&' && buf[g + 1] == '&')
	{
		buf[g] = 0;
		g++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[g] == ';')
	{
		buf[g] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*p = g;

	return (1);
}

/**
 * check_chain - This func will check if we should
 * continue chaining based on last status or not
 *
 * @info: This is the parameter struct of our prog
 *
 * @buf: This is the character buffer of our prog
 *
 * @p: Just a pointer
 *
 * @i: A pointer to the starting position in buf
 *
 * @len: length
 *
 * Return: Void
 *
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t g = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			g = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			g = len;
		}
	}

	*p = g;
}

/**
 * replace_alias - This Function replaces an
 * aliases in the tokenized string of our prog
 *
 * @info: This is the parameter struct of our prog
 *
 * Return: 1(REPLACED), else 0
 *
 */

int replace_alias(info_t *info)
{
	list_t *node;
	char *p;
	int f;

	for (f = 0; f < 10; f++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
		{
			return (0);
		}
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
		{
			return (0);
		}
		p = _strdup(p + 1);
		if (!p)
		{
			return (0);
		}
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - This function will replace
 * vars in the tokenized string of this prog
 *
 * @info: this is the parameter struct of our prog
 *
 * Return: 1 (REPLACED), else 0
 *
 */

int replace_vars(info_t *info)
{
	list_t *node;
	int f = 0;

	for (f = 0; info->argv[f]; f++)
	{
		if (info->argv[f][0] != '$' || !info->argv[f][1])
			continue;

		if (!_strcmp(info->argv[f], "$?"))
		{
			replace_string(&(info->argv[f]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[f], "$$"))
		{
			replace_string(&(info->argv[f]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[f][1], '=');
		if (node)
		{
			replace_string(&(info->argv[f]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[f], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - This function will only
 * replace a string in our program
 *
 * @old: Pointer to the old string
 *
 * @new: Pointer to the new string
 *
 * Return: 1 (REPLACED), else 0
 *
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
