#include "BlessBenShell.h"

/**
 * is_cmd - This func determines if a file is an executable command
 * @bensInfo: This is the information struct of our prog
 * @path: This is the path
 * Return: 1(TRUE), else 0
 */

int is_cmd(info_t *bensInfo, char *path)
{
	struct stat st;

	(void)bensInfo;
	if (!path || stat(path, &st))
	{
		return (0);
	}
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - This func simply duplicates a char
 * @pathstr: This is the PATH
 * @start: Index to start with/from
 * @stop: Index to stop at
 * Return: Just a pointer
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	static char blessbuf[1024];
	int k = 0, i = 0;

	for (i = 0, k = start; k < stop; k++)
		if (pathstr[k] != ':')
			blessbuf[i++] = pathstr[k];
	blessbuf[i] = 0;
	return (blessbuf);
}

/**
 * find_path - This func simply finds PATh
 * @bensInfo: This is the informmation struct
 * @pathstr: This is the PATH
 * @cmd: the commandd
 * Return: PATH or NULL
 */

char *find_path(info_t *bensInfo, char *pathstr, char *cmd)
{
	int k = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
	{
		return (NULL);
	}
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(bensInfo, cmd))
		{
			return (cmd);
		}
	}
	while (1)
	{
		if (!pathstr[k] || pathstr[k] == ':')
		{
			path = dup_chars(pathstr, curr_pos, k);
			if (!*path)
			{
				_strcat(path, cmd);
			}
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(bensInfo, path))
			{
				return (path);
			}
			if (!pathstr[k])
				break;
			curr_pos = k;
		}
		k++;
	}
	return (NULL);
}
