#include "BlessBenShell.h"

/**
 *_atoi - This func will be the one to
 * convert strings to integers in our prog
 *@s: ths is the string
 *Return: 0 if no numbers in string
 */

int _atoi(char *s)
{
	unsigned int result = 0;
	int k, sign = 1, flag = 0, output;

	for (k = 0;  s[k] != '\0' && flag != 2; k++)
	{
		if (s[k] == '-')
		{
			sign *= -1;
		}

		if (s[k] >= '0' && s[k] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[k] - '0');
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

/**
 * interactive - This func will just
 * return true when the shell is interactive mode
 * @bensInfo: This will represent the
 * struct address of our prog
 * Return: 1(interactive mode), else 0
 */

int interactive(info_t *bensInfo)
{
	return (isatty(STDIN_FILENO) && bensInfo->readfd <= 2);
}

/**
 * is_delim - This func will simply check if
 * a char in our prog is a delimeter
 * @c: This is the char to check in our prog
 * @delim: This represents the delimeter
 * string in our prog
 * Return: 1(True), else 0 (False)
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
 *_isalpha - This is the func that should check for
 * characters that are alphabetic in our prog
 *@c: Input
 *Return: 1(ALPHABETIC), else 0
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
