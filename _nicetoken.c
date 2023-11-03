#include "BlessBenShell.h"

/**
 * **strtow - This func simply divides a string into words
 * @str: This is the input
 * @d: This string is the delimeter
 * Return: Just a pointer
 */

char **strtow(char *str, char *d)
{
	int k, l, i, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
	{
		d = " ";
	}
	for (k = 0; str[k] != '\0'; k++)
	{
		if (!is_delim(str[k], d) && (is_delim(str[k + 1], d) || !str[k + 1]))
			numwords++;
	}
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[k], d))
			k++;
		i = 0;
		while (!is_delim(str[k + i], d) && str[k + i])
			i++;
		s[l] = malloc((i + 1) * sizeof(char));
		if (!s[l])
		{
			for (i = 0; i < l; i++)
				free(s[i]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[l][m] = str[k++];
		s[l][m] = 0;
	}
	s[l] = NULL;
	return (s);
}

/**
 * **strtow2 - This func will divide a string to words
 * @str: input
 * @d: program delimeter
 * Return: Just a pointer
 */

char **strtow2(char *str, char d)
{
	int k, l, i, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (k = 0; str[k] != '\0'; k++)
		if ((str[k] != d && str[k + 1] == d) ||
		    (str[k] != d && !str[k + 1]) || str[k + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (k = 0, l = 0; l < numwords; l++)
	{
		while (str[k] == d && str[k] != d)
			k++;
		i = 0;
		while (str[k + i] != d && str[k + i] && str[k + i] != d)
			i++;
		s[l] = malloc((i + 1) * sizeof(char));
		if (!s[l])
		{
			for (i = 0; i < j; i++)
				free(s[i]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < i; m++)
			s[l][m] = str[k++];
		s[l][m] = 0;
	}
	s[l] = NULL;

	return (s);
}
