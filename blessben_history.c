#include "myShellHeader.h"

/**
 * get_history_file - This func only gets the history file in this program
 *
 * @info: This is the parameter struct in our program.
 *
 * Return: string containg the history.
 *
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
	{
		return (NULL);
	}
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
	{
		return (NULL);
	}
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - This func will only create a file
 * or append a file to an existing one.
 *
 * @info: This is the parameter struct of our program.
 *
 * Return: 1 (success), else -1.
 *
 */

int write_history(info_t *info)
{
	char *filename = get_history_file(info);
	ssize_t fd;
	list_t *node = NULL;

	if (!filename)
	{
		return (-1);
	}

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
	{
		return (-1);
	}
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - This func will read the
 * history from a file in our program.
 *
 * @info: This is the parameter struct of our program.
 *
 * Return: histcount (success), else 0(failure).
 *
 */

int read_history(info_t *info)
{
	struct stat st;
	ssize_t fd, rdlen, fsize = 0;
	char *buf = NULL, *filename = get_history_file(info);
	int f, last = 0, linecount = 0;

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (f = 0; f < fsize; f++)
		if (buf[f] == '\n')
		{
			buf[f] = 0;
			build_history_list(info, buf + last, linecount++);
			last = f + 1;
		}
	if (last != f)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - This fun only adds
 * entry to a history linked list in our program
 *
 * @info: This is the structure that contains arguments.
 *
 * @buf: Represents the buffer.
 *
 * @linecount: This is the history linecount,
 * histcount in our program.
 *
 * Return: 0 (Always).
 *
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
	{
		node = info->history;
	}
	add_node_end(&node, buf, linecount);

	if (!info->history)
	{
		info->history = node;
	}
	return (0);
}

/**
 * renumber_history - This func will only renumber
 * the history linked list after changes in our program.
 *
 * @info: This is the structure that contains arguments.
 *
 * Return: histcount.
 *
 */

int renumber_history(info_t *info)
{
	int f = 0;
	list_t *node = info->history;

	while (node)
	{
		node->num = f++;
		node = node->next;
	}
	return (info->histcount = f);
}
