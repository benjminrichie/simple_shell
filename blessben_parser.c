#include "myShellHeader.h"

/**
 * is_cmd - This func will check if a
 * file is an executable command
 *
 * @info: This is the info struct of our prog
 *
 * @path: path
 *
 * Return: 1(True), else 0
 *
 */

int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
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
 * dup_chars - This func only duplicates char
 *
 * @pathstr: This represents the PATH string
 *
 * @start: This represents the starting index of our prog
 *
 * @stop: This will be the index to stop at
 *
 * Return: Just the pointer
 *
 */

char *dup_chars(char *pathstr, int start, int stop)
{
	int f = 0, e = 0;
	static char buf[1024];

	for (e = 0, f = start; f < stop; f++)
		if (pathstr[f] != ':')
		{
			buf[e++] = pathstr[f];
		}
	buf[e] = 0;
	return (buf);
}

/**
 * find_path - This func simply finds the cmd in the PATH string
 *
 * @info: This is the info struct of our prog
 *
 * @pathstr: This is the PATH string of our prog
 *
 * @cmd: This is cmd we are finding
 *
 * Return: cmd path(if found), else NULL
 *
 */

char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int f = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
	{
		return (NULL);
	}
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
		{
			return (cmd);
		}
	}
	while (1)
	{
		if (!pathstr[f] || pathstr[f] == ':')
		{
			path = dup_chars(pathstr, curr_pos, f);
			if (!*path)
			{
				_strcat(path, cmd);
			}
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
			{
				return (path);
			}
			if (!pathstr[f])
				break;
			curr_pos = f;
		}
		f++;
	}
	return (NULL);
}
