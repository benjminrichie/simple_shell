#include "BlessBenShell.h"

/**
 * _historywriteme - This func simply creates or
 * appends to an already existing file
 * @bensInfo: To represent the
 * parameter struct in our prog
 * Return: 1(SUCCESS), else -1
 */

int _historywriteme(info_t *bensInfo)
{
	ssize_t fd;
	char *filename = get_blessings_history(bensInfo);
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
	for (node = bensInfo->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);

	return (1);
}

/**
 * get_blessings_history - This func will get the history for us
 * @bensInfo: Represents just a parameter struct in our prog
 * Return: the string containg history file for the prog.
 */

char *get_blessings_history(info_t *bensInfo)
{
	char *blessbuf, *blessdir;

	blessdir = _getenv(bensInfo, "HOME=");
	if (!blessdir)
	{
		return (NULL);
	}
	blessbuf = malloc(sizeof(char) * (_strlen(blessdir) + _strlen(HIST_FILE) + 2));
	if (!blessbuf)
	{
		return (NULL);
	}
	blessbuf[0] = 0;
	_strcpy(blessbuf, blessdir);
	_strcat(blessbuf, "/");
	_strcat(blessbuf, HIST_FILE);
	return (blessbuf);
}

/**
 * _the_history_builder - This func simply
 * adds entry to a history linked listin our prog
 * @bensInfo: To represent the structure containing
 * potential arguments in our prog
 * @blessbuf: This is just our buffer
 * @counteachline: This is the line counter
 * Return: Always 0
 */

int _the_history_builder(info_t *bensInfo, char *blessbuf, int counteachline)
{
	list_t *node = NULL;

	if (bensInfo->history)
		node = bensInfo->history;
	add_node_end(&node, blessbuf, counteachline);

	if (!bensInfo->history)
		bensInfo->history = node;
	return (0);
}

/**
 * _renumMyhistoryF - This func will renumber
 * the history list in our prog after changes
 * @bensInfo: this is the structure containing potential arguments in our prog
 * Return: just return the new histcount
 */

int _renumMyhistoryF(info_t *bensInfo)
{
	list_t *node = bensInfo->history;
	int k = 0;

	while (node)
	{
		node->num = k++;
		node = node->next;
	}
	return (bensInfo->histcount = k);
}

/**
 * _historyreadme - This func will read history from
 * a file in our prog.
 * @bensInfo: This is the parameter struct in our prog.
 * Return: The history count(SUCCESS), else 0
 */

int _historyreadme(info_t *bensInfo)
{
	int k, MyLast = 0, counteachline = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_blessings_history(bensInfo);

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
	for (k = 0; k < fsize; k++)
		if (buf[k] == '\n')
		{
			buf[k] = 0;
			_the_history_builder(bensInfo, buf + MyLast, counteachline++);
			MyLast = k + 1;
		}
	if (MyLast != k)
		_the_history_builder(bensInfo, buf + MyLast, counteachline++);
	free(buf);
	bensInfo->histcount = counteachline;
	while (bensInfo->histcount-- >= HIST_MAX)
		delete_node_at_index(&(bensInfo->history), 0);
	_renumMyhistoryF(bensInfo);
	return (bensInfo->histcount);
}
