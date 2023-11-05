#include "shell.h"

/**
 * input_buf - This func simply will buffer
 * chained commands in our prog
 *
 * @info: This is the parameter struct of our prog
 *
 * @buf: This is the address of buffer of our prog
 *
 * @len: This is the address of len var
 *
 * Return: bytes
 *
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	size_t len_p = 0;
	ssize_t u = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		u = getline(buf, &len_p, stdin);
#else
		u = _getline(info, buf, &len_p);
#endif
		if (u > 0)
		{
			if ((*buf)[u - 1] == '\n')
			{
				(*buf)[u - 1] = '\0'; /* remove trailing newline */
				u--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = u;
				info->cmd_buf = buf;
			}
		}
	}
	return (u);
}

/**
 * get_input - This func will get a line minus the newline
 *
 * @info: This is the parameter struct of our Prog
 *
 * Return: bytes read
 *
 */

ssize_t get_input(info_t *info)
{
	char **buf_p = &(info->arg), *p;
	ssize_t u = 0;
	static size_t f, g, len;
	static char *buf; /* the ';' command chain buffer */

	_putchar(BUF_FLUSH);
	u = input_buf(info, &buf, &len);
	if (u == -1) /* EOF */
	{
		return (-1);
	}
	if (len)
	{
		g = f;
		p = buf + f; /* get pointer for return */

		check_chain(info, buf, &g, f, len);
		while (g < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &g))
				break;
			g++;
		}

		f = g + 1;
		if (f >= len) /* reached end of buffer? */
		{
			f = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (u); /* return length of buffer from _getline() */
}

/**
 * read_buf - This func will only read a buffer in our prog
 *
 * @info: This is the parameter struct of our prog
 *
 * @buf: Representing the buffer
 *
 * @i: Represents size
 *
 * Return: r
 *
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t u = 0;

	if (*i)
	{
		return (0);
	}
	u = read(info->readfd, buf, READ_BUF_SIZE);
	if (u >= 0)
	{
		*i = u;
	}
	return (u);
}

/**
 * _getline - This func only gets the next
 * line of input from STDIN in this prog
 *
 * @info: This is the parameter struct of our prog
 *
 * @ptr: Just a pointer
 *
 * @length: This is the size of previously
 * allocated ptr buffer if not NULL
 *
 * Return: s
 *
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	char *p = NULL, *new_p = NULL, *c;
	static size_t f, len;
	ssize_t u = 0, s = 0;
	size_t e;
	static char buf[READ_BUF_SIZE];


	p = *ptr;
	if (p && length)
		s = *length;
	if (f == len)
		f = len = 0;

	u = read_buf(info, buf, &len);
	if (u == -1 || (u == 0 && len == 0))
		return (-1);

	c = _strchr(buf + f, '\n');
	e = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + e : e + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + f, e - f);
	else
		_strncpy(new_p, buf + f, e - f + 1);

	s += e - f;
	f = e;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - This func will only block ctrl-C
 *
 * @sig_num: This represents the signal number
 *
 * Return: void
 *
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
