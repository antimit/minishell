#include "builtins.h"
#include "minishell.h" // Для доступа к g_exit_status
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

int builtin_cd(char **args)
{
    char *dir;

    if (args[2] != NULL)
    {
        fprintf(stderr, "minishell: cd: too many arguments\n");
        g_exit_status = 1;
        return (1);
    }

    if (!args[1] || strcmp(args[1], "~") == 0)
        dir = getenv("HOME");
    else
        dir = args[1];

    if (chdir(dir) != 0)
    {
        perror("minishell");
        g_exit_status = 1;
        return (1);
    }

    return (SUCCESS1);
}
