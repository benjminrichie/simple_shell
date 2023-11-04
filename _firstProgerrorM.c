#include "BlessBenShell.h"

/**
 * _mycommentremover - This prog replace first iteration of # with \0
 * @blessbuf: just a pointer
 * Return: 0(Always)
 */

void _mycommentremover(char *blessbuf)
{
	int k = 0;

	for (k = 0; blessbuf[k] != '\0'; k++)
		if (blessbuf[k] == '#' && (!k || blessbuf[k - 1] == ' '))
		{
			blessbuf[k] = '\0';
			break;
		}
}

/**
 * BenerratoiBless - This func converts a string to an integer in this prog
 * @Dstring: This is the string
 * Return: 0(string), else -1(error)
 */

int BenerratoiBless(char *Dstring)
{
	int k = 0;
	unsigned long int result = 0;

	if (*Dstring == '+')
	{
		Dstring++;
	}
	for (k = 0;  Dstring[k] != '\0'; k++)
	{
		if (Dstring[k] >= '0' && Dstring[k] <= '9')
		{
			result *= 10;
			result += (Dstring[k] - '0');
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
 * convert_number - This is a clone(converter function)
 * @base: This represents the base of our prog
 * @num: This represents the number
 * @flags: This represents the argument flags
 * Return: just the string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char DsignS = 0;
	char *ptr;
	unsigned long q = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		q = -num;
		DsignS = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[q % base];
		q /= base;
	} while (q != 0);

	if (DsignS)
		*--ptr = DsignS;

	return (ptr);
}

/**
 * echo_errorPrint - This func is to print error messages in our prog
 * @bensInfo: This is the parameter
 * @estrspecified: This is the string with specific type of error
 * Return: 0(!string), else -1(error)
 */

void echo_errorPrint(info_t *bensInfo, char *estrspecified)
{
	_eputs(bensInfo->fname);
	_eputs(": ");
	print_d(bensInfo->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(bensInfo->argv[0]);
	_eputs(": ");
	_eputs(estrspecified);
}

/**
 * print_d - This function simply
 * prints a decimal number
 * @_dinput: the input in our prog
 * @fd: the filedescriptor in our prog
 * Return: char printed
 */

int print_d(int _dinput, int fd)
{
	int k, countme = 0;
	unsigned int _abs_, current;
	int (*__putchar)(char) = _putchar;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (_dinput < 0)
	{
		_abs_ = -_dinput;
		__putchar('-');
		countme++;
	}
	else
		_abs_ = _dinput;
	current = _abs_;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (_abs_ / k)
		{
			__putchar('0' + current / k);
			countme++;
		}
		current %= k;
	}
	__putchar('0' + current);
	countme++;

	return (countme);
}
