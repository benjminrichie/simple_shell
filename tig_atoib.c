#include "shell.h"

/**
 * interactive - This func will return
 * true if shell is interactive mode
 *
 * @info: This is struct address of our prog
 *
 * Return: 1 (interactive mode), else 0
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - This func will check if char is a delimeter
 *
 * @c: This is the char to be checked
 * @delim: This is the delimeter string
 *
 * Return: 1 (true), Else 0 (false)
 *
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
		{
			return (1);
		}
	return (0);
}

/**
 *_isalpha - This func checks for alphabetic char
 *@c: This is the input char
 *Return: 1 (alphabetic), else 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 *_atoi - This func simply tries to convert a str to an int
 *@s: This is the string
 *Return: 0
 */

int _atoi(char *s)
{
	int f, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (f = 0;  s[f] != '\0' && flag != 2; f++)
	{
		if (s[f] == '-')
		{
			sign *= -1;
		}

		if (s[f] >= '0' && s[f] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[f] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sign == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}

	return (output);
}
