#include "shell.h"

/**
 * _erratoi - This func will only convert
 * strings to an integer in our prog
 *
 * @s: This is the str
 *
 * Return: 0 (No number) eise -1 (Error)
 *
 */

int _erratoi(char *s)
{
	int f = 0;
	unsigned long int result = 0;

	if (*s == '+')
	{
		s++;
	}
	for (f = 0;  s[f] != '\0'; f++)
	{
		if (s[f] >= '0' && s[f] <= '9')
		{
			result *= 10;
			result += (s[f] - '0');
			if (result > INT_MAX)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
	}
	return (result);
}

/**
 * print_error - This func simply prints
 * error message to our prog
 *
 * @info: This is the parameter
 * and return info struct of our prog
 *
 * @estr: This is the string that contains
 * specified error type in our prog
 *
 * Return: 0 (No number converted) else -1 (Error)
 *
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - A customprog that will only print
 * a base 10 decimal int number in our prog
 *
 * @input: This represents input
 *
 * @fd: Representing filedescriptor
 *
 * Return: char
 *
 */

int print_d(int input, int fd)
{
	int f, count = 0;
	int (*__putchar)(char) = _putchar;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
	{
		__putchar = _eputchar;
	}
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
	{
		_abs_ = input;
	}
	current = _abs_;
	for (f = 1000000000; f > 1; f /= 10)
	{
		if (_abs_ / f)
		{
			__putchar('0' + current / f);
			count++;
		}
		current %= f;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - This is our converter
 * function (clone of itoa) for this program
 *
 * @num: Representing a number in our prog
 *
 * @base: Representing the base in our prog
 *
 * @flags: Representing the argument flags
 *
 * Return: Just a string
 *
 */

char *convert_number(long int num, int base, int flags)
{
	char *ptr;
	char sign = 0;
	unsigned long n = num;
	static char buffer[50];
	static char *array;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
	{
		*--ptr = sign;
	}
	return (ptr);
}

/**
 * remove_comments - This is a replacement function that
 * replaces the first instance of '#' with '\0' in our prog
 *
 * @buf: This is an address
 *
 * Return: 0 (Always)
 *
 */

void remove_comments(char *buf)
{
	int f;

	for (f = 0; buf[f] != '\0'; f++)
		if (buf[f] == '#' && (!f || buf[f - 1] == ' '))
		{
			buf[f] = '\0';
			break;
		}
}
