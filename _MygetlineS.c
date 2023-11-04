#include "BlessBenShell.h"

/**
 * sigintHandler - This func blocks ctrl-C in our prog
 * @sig_num: This is the signal number in our prog
 * Return: Nothing(void)
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * get_input - This func gets a line - newline in this prog
 *
 * @bensInfo: This is the parameter struct in our prog
 *
 * Return: bytes
 *
 */

ssize_t get_input(info_t *bensInfo)
{
	static size_t k, l, len;
	static char *blessbuf;
	char **buf_p = &(bensInfo->arg), *point;
	ssize_t z = 0;

	_putchar(BUF_FLUSH);
	z = input_buf(bensInfo, &blessbuf, &len);
	if (z == -1) /* EOF */
	{
		return (-1);
	}
	if (len)
	{
		l = k;
		point = blessbuf + k; /* get pointer for return */

		check_chain(bensInfo, blessbuf, &l, k, len);
		while (l < len)
		{
			if (is_chain(bensInfo, blessbuf, &l))
				break;
			l++;
		}

		k = l + 1;
		if (l >= len)
		{
			l = len = 0;
			bensInfo->cmd_buf_type = CMD_NORM;
		}

		*buf_p = point;
		return (_strlen(point));
	}

	*buf_p = blessbuf;
	return (z);
}

/**
 * input_buf -This func contains buffer chained cmd
 *
 * @bensInfo: This is the parameter struct of our prog
 *
 * @blessbuf: buffer address
 *
 * @len: This is the lenvar address
 *
 * Return: bytes read
 */

ssize_t input_buf(info_t *bensInfo, char **blessbuf, size_t *len)
{
	size_t len_p = 0;
	ssize_t z = 0;

	if (!*len)
	{
		free(*blessbuf);
		*blessbuf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		z = getline(blessbuf, &len_p, stdin);
#else
		z = _getline(bensInfo, blessbuf, &len_p);
#endif
		if (z > 0)
		{
			if ((*blessbuf)[z - 1] == '\n')
			{
				(*blessbuf)[z - 1] = '\0';
				z--;
			}
			bensInfo->linecount_flag = 1;
			remove_comments(*blessbuf);
			build_history_list(bensInfo, *blessbuf, bensInfo->histcount++);
			{
				*len = z;
				bensInfo->cmd_buf = blessbuf;
			}
		}
	}
	return (z);
}

/**
 * read_buf - This func will simply
 * read a buffer in our prog
 * @bensInfo: This is the parameter struct in our prog
 * @blessbuf: This is the buffer in our prog
 * @k: size
 * Return: z
 */

ssize_t read_buf(info_t *bensInfo, char *blessbuf, size_t *k)
{
	ssize_t z = 0;

	if (*k)
	{
		return (0);
	}
	z = read(bensInfo->readfd, blessbuf, READ_BUF_SIZE);
	if (z >= 0)
	{
		*k = z;
	}
	return (z);
}

/**
 * _getline - This func simply will get
 * from STDIN the next line of input
 *
 * @bensInfo: This is the parameter struct in our prog
 *
 * @ptr: Just a pointer to buffer
 *
 * @length: This is the size of ptr
 * buffer that was allocated previously
 *
 * Return: s
 */

int _getline(info_t *bensInfo, char **ptr, size_t *length)
{
	size_t i;
	ssize_t z = 0, s = 0;
	char *point = NULL, *new_p = NULL, *c;
	static char blessbuf[READ_BUF_SIZE];
	static size_t k, len;

	point = *ptr;
	if (point && length)
	{
		s = *length;
	}
	if (k == len)
	{
		k = len = 0;
	}
	z = read_buf(bensInfo, blessbuf, &len);
	if (z == -1 || (z == 0 && len == 0))
	{
		return (-1);
	}
	c = _strchr(blessbuf + k, '\n');
	i = c ? 1 + (unsigned int)(c - blessbuf) : len;
	new_p = _realloc(point, s, s ? s + i : i + 1);
	if (!new_p)
		return (point ? free(point), -1 : -1);
	if (s)
		_strncat(new_p, blessbuf + k, i - k);
	else
		_strncpy(new_p, blessbuf + k, i - k + 1);

	s += i - k;
	k = i;
	point = new_p;

	if (length)
		*length = s;
	*ptr = point;

	return (s);
}
