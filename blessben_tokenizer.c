#include "myShellHeader.h"

/**
 * **strtow - This func will only split a string into words
 *
 * @str: This is the input
 *
 * @d: This is the delimeter
 *
 * Return: A pointer (SUCCESS), or NULL (FAILURE)
 */

char **strtow(char *str, char *d)
{
	char **s;
	int f, g, e, m, numwords = 0;

	if (str == NULL || str[0] == 0)
	{
		return (NULL);
	}
	if (!d)
		d = " ";
	for (f = 0; str[f] != '\0'; f++)
	{
		if (!is_delim(str[f], d) && (is_delim(str[f + 1], d) || !str[f + 1]))
			numwords++;
	}
	if (numwords == 0)
	{
		return (NULL);
	}
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (f = 0, g = 0; g < numwords; g++)
	{
		while (is_delim(str[f], d))
			f++;
		e = 0;
		while (!is_delim(str[f + e], d) && str[f + e])
			e++;
		s[g] = malloc((e + 1) * sizeof(char));
		if (!s[g])
		{
			for (e = 0; e < g; e++)
				free(s[e]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < e; m++)
			s[g][m] = str[f++];
		s[g][m] = 0;
	}
	s[g] = NULL;
	return (s);
}

/**
 * **strtow2 - This func simply splits
 * a string into words in our prog
 *
 * @str: This is the input
 *
 * @d: This is the delimeter
 *
 * Return: pointer to array(SUCCESS), else NULL(FAILURE)
 *
 */

char **strtow2(char *str, char d)
{
	char **s;
	int f, g, e, m, numwords = 0;

	if (str == NULL || str[0] == 0)
	{
		return (NULL);
	}
	for (f = 0; str[f] != '\0'; f++)
		if ((str[f] != d && str[f + 1] == d) ||
		    (str[f] != d && !str[f + 1]) || str[f + 1] == d)
			numwords++;
	if (numwords == 0)
	{
		return (NULL);
	}
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (f = 0, g = 0; g < numwords; g++)
	{
		while (str[f] == d && str[f] != d)
			f++;
		e = 0;
		while (str[f + e] != d && str[f + e] && str[f + e] != d)
			e++;
		s[g] = malloc((e + 1) * sizeof(char));
		if (!s[g])
		{
			for (e = 0; e < g; e++)
				free(s[e]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < e; m++)
			s[g][m] = str[f++];
		s[g][m] = 0;
	}
	s[g] = NULL;
	return (s);
}
