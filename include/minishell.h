#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <ctype.h>
# include <limits.h>

# include "builtins.h"
# include "executor.h"
# include "parser.h"
# include "signals.h"
# include "utils.h"
# include "error.h"
# include "libft.h"
# define EXIT_SHELL 100
# define SUCCESS 0
# define IN 0
# define OUT 1

# define TRUE 1
# define FALSE 0
// # define SUCCESS 1
# define FAILED 0


extern volatile sig_atomic_t g_signal;
extern volatile sig_atomic_t g_in_child;
extern volatile sig_atomic_t  g_exit_status;

typedef struct s_command
{
    char                **args;
    char                *input_redir;
    char                *output_redir;
    int                 append; // 1 for >>, 0 for >
    struct s_command    *next;
}   t_command;


typedef struct s_env
{
    char * key_pair;
    struct s_env * next;
} t_env;


# define NO_REDIRECT -1

// int handle_redirections(t_command *cmd);
#endif
