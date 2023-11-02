#include "BlessBenShell.h"

/**
 * informationIsCleared - This is what will
 * initialize the info_t struct of our Prog
 * @bensInfo: struct address
 */

void informationIsCleared(info_t *bensInfo)
{
	bensInfo->arg = NULL;
	bensInfo->argv = NULL;
	bensInfo->path = NULL;
	bensInfo->argc = 0;
}

/**
 * informationIsSet - This simply initializes info_t struct of our prog.
 * @bensInfo: This will just represent the struct address of our prog.
 * @av: This will be represented as the argument vector of our Prog
 */

void informationIsSet(info_t *bensInfo, char **av)
{
	int k = 0;

	bensInfo->fname = av[0];
	if (bensInfo->arg)
	{
		info->argv = strtow(bensInfo->arg, " \t");
		if (!bensInfo->argv)
		{

			bensInfo->argv = malloc(sizeof(char *) * 2);
			if (bensInfo->argv)
			{
				bensInfo->argv[0] = _strdup(bensInfo->arg);
				bensInfo->argv[1] = NULL;
			}
		}
		for (k = 0; bensInfo->argv && bensInfo->argv[k]; k++)
			;
		bensInfo->argc = k;

		replace_alias(bensInfo);
		replace_vars(bensInfo);
	}
}

/**
 * informationIsFreed - This is the func that
 * frees info_t struct fields of our prog
 * @bensInfo: struct address
 * @MeAndBlessing: true if freeing all fields
 */

void informationIsFreed(info_t *bensInfo, int MeAndBlessing)
{
	ffree(bensInfo->argv);
	bensInfo->argv = NULL;
	bensInfo->path = NULL;
	if (MeAndBlessing)
	{
		if (!bensInfo->cmd_buf)
			free(bensInfo->arg);
		if (bensInfo->env)
			free_list(&(bensInfo->env));
		if (bensInfo->history)
			free_list(&(bensInfo->history));
		if (bensInfo->alias)
			free_list(&(bensInfo->alias));
		ffree(bensInfo->environ);
			bensInfo->environ = NULL;
		bfree((void **)bensInfo->cmd_buf);
		if (bensInfo->readfd > 2)
			close(bensInfo->readfd);
		_putchar(BUF_FLUSH);
	}
}
