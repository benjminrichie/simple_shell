#include "BlessBenShell.h"

/**
 * hsh - This function is themain shell loop for our prog
 * @bensInfo: the parameter prog
 * @av: the argument vectorfor the prog
 * Return: 0(success), else 1(error)
 */

int hsh(info_t *bensInfo, char **av)
{
	ssize_t z = 0;
	int builtin_ret = 0;

	while (z != -1 && builtin_ret != -2)
	{
		informationIsCleared(bensInfo);
		if (interactive(bensInfo))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		z = get_input(bensInfo);
		if (z != -1)
		{
			informationIsSet(bensInfo, av);
			builtin_ret = find_builtin(bensInfo);
			if (builtin_ret == -1)
				find_cmd(bensInfo);
		}
		else if (interactive(bensInfo))
			_putchar('\n');
		informationIsFreed(bensInfo, 0);
	}
	_historywriteme(bensInfo);
	informationIsFreed(bensInfo, 1);
	if (!interactive(bensInfo) && bensInfo->status)
		exit(bensInfo->status);
	if (builtin_ret == -2)
	{
		if (bensInfo->err_num == -1)
			exit(bensInfo->status);
		exit(bensInfo->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - This will simply just find a builtin cmd
 *
 * @bensInfo: This is the parameter
 *
 * Return: -1 (not found), else if 0 (Success)
 * else if 1 (!not found !successful) else-2 (exit)
 */

int find_builtin(info_t *bensInfo)
{
	int k, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (k = 0; builtintbl[k].type; k++)
		if (_strcmp(bensInfo->argv[0], builtintbl[k].type) == 0)
		{
			bensInfo->line_count++;
			built_in_ret = builtintbl[k].func(bensInfo);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - This func finds a cmd PATH
 * @bensInfo: This is the parameter
 * Return: Nothing
 */

void find_cmd(info_t *bensInfo)
{
	char *path = NULL;
	int k, i;

	bensInfo->path = bensInfo->argv[0];
	if (bensInfo->linecount_flag == 1)
	{
		bensInfo->line_count++;
		bensInfo->linecount_flag = 0;
	}
	for (k = 0, i = 0; bensInfo->arg[k]; k++)
		if (!is_delim(bensInfo->arg[k], " \t\n"))
			i++;
	if (!i)
		return;

	path = find_path(bensInfo, _getenv(info, "PATH="), bensInfo->argv[0]);
	if (path)
	{
		bensInfo->path = path;
		fork_cmd(bensInfo);
	}
	else
	{
		if ((interactive(bensInfo) || _getenv(bensInfo, "PATH=")
			|| bensInfo->argv[0][0] == '/') && is_cmd(bensInfo, bensInfo->argv[0]))
			fork_cmd(bensInfo);
		else if (*(bensInfo->arg) != '\n')
		{
			bensInfo->status = 127;
			print_error(bensInfo, "not found\n");
		}
	}
}

/**
 * fork_cmd - This func simply forks a an exec
 * @bensInfo: This is the parameter
 * Return: Nothing
 */

void fork_cmd(info_t *bensInfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(bensInfo->path, bensInfo->argv, get_environ(bensInfo)) == -1)
		{
			informationIsFreed(bensInfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(bensInfo->status));
		if (WIFEXITED(bensInfo->status))
		{
			bensInfo->status = WEXITSTATUS(bensInfo->status);
			if (bensInfo->status == 126)
				print_error(bensInfo, "Permission denied\n");
		}
	}
}
