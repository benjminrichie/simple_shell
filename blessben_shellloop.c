#include "shell.h"

/**
 * hsh - This function is the
 * main shell loop of this program
 *
 * @info: This is the parameter
 * info struct of this prog
 *
 * @av: This is the argument vector
 * from main()
 *
 * Return: 0 (success), else if 1 (error),
 * else (error code)
 *
 */

int hsh(info_t *info, char **av)
{
	int builtin_ret = 0;
	ssize_t u = 0;

	while (u != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
		{
			_puts("$ ");
		}
		_eputchar(BUF_FLUSH);
		u = get_input(info);
		if (u != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
			{
				find_cmd(info);
			}
		}
		else if (interactive(info))
		{
			_putchar('\n');
		}
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
	{
		exit(info->status);
	}
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
		{
			exit(info->status);
		}
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - This function is to find
 * a built-in command in our program
 *
 * @info: This is the parameter
 * info struct of this prog
 *
 * Return: -1 (builtin not found), else if 0 (builtin executed successfully),
 * else if 1 (builtin found but not successful),
 * else -2 (builtin signals exit())
 *
 */

int find_builtin(info_t *info)
{
	int f, built_in_ret = -1;
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

	for (f = 0; builtintbl[f].type; f++)
	{
		if (_strcmp(info->argv[0], builtintbl[f].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[f].func(info);
			break;
		}
	}
	return (built_in_ret);
}

/**
 * find_cmd - This func simply finds a
 * command in the PATH of our prog
 *
 * @info: This is the parameter info struct of our prog
 *
 * Return: void
 *
 */

void find_cmd(info_t *info)
{
	int f, e;
	char *path = NULL;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (f = 0, e = 0; info->arg[f]; f++)
	{
		if (!is_delim(info->arg[f], " \t\n"))
		{
			e++;
		}
	}
	if (!e)
	{
		return;
	}

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - This function simply
 * forks an exec thread to run cmd
 *
 * @info: This is the parameter
 * info struct of our prog
 *
 * Return: void
 *
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
			{
				exit(126);
			}
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
