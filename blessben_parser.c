#include "mygroupedshell.h"

/**
 * is_cmd - This function will check if a
 * file is an executable command.
 *
 * @info: The info struct of our program.
 *
 * @path: The path.
 *
 * Return: Return 1(True), */

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
<<<<<<< HEAD
 * dup_chars - This function only duplicates char.
 *
 * @pathstr: Represents the PATH string.
 *
 * @start: Represents the starting index of our program.
 *
 * @stop: This will be the index to stop at.
 *
 * Return: Return just the pointer.
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
 * find_path - This func simply finds the cmd in the PATH string.
 *
 * @info: The info struct of our program.
 *
 * @pathstr: This is the PATH string of our program.
 *
 * @cmd: The cmd we are finding.
 *
 * Return: Return cmd path(if found), else NULL.
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
