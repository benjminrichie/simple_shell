#ifndef BlessBenShell_H
#define BlessBenShell_H

#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/wait.h>

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

extern char **environ;


/**
 * struct liststr - This prog is a singly linked
 * list. And the func can be called
 *
 * @num: This is just the number
 *
 * @str: This simply represents a string
 *
 * @next: Just a pointer that points
 * to the next node in our prog
 *
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - This func will contain pseudo-arguements
 *to pass into a function. This will allow uniform prototype
 *for function pointer struct in this prog
 *@arg: This is a string generated from getline containing arguements
 *@argv: This is an array of strings generated from arg
 *@path: This is a string path for the current command
 *@argc: This is the argument count
 *@line_count: This is the error count
 *@err_num: This is the error code for exit()s
 *@linecount_flag: Checks if on count this line of input
 *@fname: This is the program filename
 *@env: This is linked list local copy of environ
 *@environ: This is custom modified copy of environ from LL env
 *@history: This is the history node
 *@alias: This is the alias node
 *@env_changed: Checks on if environ was changed
 *@status: checks the return status of the last exec'd command
 *@cmd_buf: This is address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: This is CMD_type ||, &&, ;
 *@readfd: This is the fd from which to read line input
 *@histcount: This is the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* loopmyshell.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* _justparse_r.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* ProgerrorM.c */
void _eputs(char *);
int _eputchar(char);
int put_myfd(char c, int fd);
int puts_myfd(char *str, int fd);

/* Funct_getsmyenviron.c */
char **_environFuncT(info_t *);
int di_setmyenviron(info_t *, char *);
int setmy_environt(info_t *, char *, char *);

/* BensInfoFunc.c */
void informationIsCleared(info_t *);
void informationIsSet(info_t *, char **);
void informationIsFreed(info_t *, int);

/* _firstProgerrorM.c */
int BenerratoiBless(char *);
void echo_errorPrint(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void _mycommentremover(char *);

/* _memoryRelease.c */
int freetiger(void **);

/* quit_exits_finish.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* _history_blessing_tiger.c */
char *get_blessings_history(info_t *bensInfo);
int _historywriteme(info_t *bensInfo);
int _historyreadme(info_t *bensInfo);
int _the_history_builder(info_t *bensInfo, char *blessbuf, int counteachline);
int _renumMyhistoryF(info_t *bensInfo);

/* _stringme.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *_tostart(const char *, const char *);
char *_strcat(char *, char *);

/* firststringme.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* _nicetoken.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* Tigrealloc_ben.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* _Atmyatoi_.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* inbuiltProg_.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* Tiger_environB.c */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* inbuiltProg_1.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* _MygetlineS.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* d_listzero.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* ben_bless_var_.c */
int _chainme(info_t *, char *, size_t *);
void _checkmychainP(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int Tigreplace_var(info_t *);
int _stringreplacement_(char **, char *);

/* d_firstlist.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

#endif
