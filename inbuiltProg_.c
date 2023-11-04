#include "BlessBenShell.h"

/**
 * _myhelp - This funct can change the
 * pwd of the process in our prog
 * @bensInfo: This is the structure that contain future arguments
 * Return: 0 (Always)
 */

int _myhelp(info_t *bensInfo)
{
	char **arg_array;

	arg_array = bensInfo->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
	{
		_puts(*arg_array);
	}
	return (0);
}

/**
 * _myexit - This is the func that is responsible
 * for exiting the shell in our prog
 * @bensInfo: This is the structure containing future arguments
 *  Return: 0(bensInfo.argv[0]) != "exit"
 */

int _myexit(info_t *bensInfo)
{
	int mexitcheckQUIT;

	if (bensInfo->argv[1])
	{
		mexitcheckQUIT = _erratoi(bensInfo->argv[1]);
		if (mexitcheckQUIT == -1)
		{
			bensInfo->status = 2;
			echo_errorPrint(bensInfo, "Illegal number: ");
			_eputs(bensInfo->argv[1]);
			_eputchar('\n');
			return (1);
		}
		bensInfo->err_num = _erratoi(bensInfo->argv[1]);
		return (-2);
	}
	bensInfo->err_num = -1;
	return (-2);
}

/**
 * _mycd - This func will only change the present directory
 * @bensInfo: This is the structure that contains future arguments
 *  Return: 0(Always)
 */
int _mycd(info_t *bensInfo)
{
	int chdir_ret;
	char *s, *dir, buffer[1024];

	s = getcwd(buffer, 1024);
	if (!s)
	{
		_puts("TODO: >>getcwd failure emsg here<<\n");
	}
	if (!bensInfo->argv[1])
	{
		dir = _environFuncT(bensInfo, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _environFuncT(bensInfo, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(bensInfo->argv[1], "-") == 0)
	{
		if (!_environFuncT(bensInfo, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_environFuncT(bensInfo, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _environFuncT(bensInfo, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(bensInfo->argv[1]);
	if (chdir_ret == -1)
		echo_errorPrint(bensInfo, "can't cd to ");
		_eputs(bensInfo->argv[1]), _eputchar('\n');
	else
		setmy_environt(bensInfo, "OLDPWD", _environFuncT(bensInfo, "PWD="));
		setmy_environt(bensInfo, "PWD", getcwd(buffer, 1024));
	return (0);
}
