// builtins.c

#include "builtins.h"
#include <stdio.h>
#include <string.h>

int builtin_echo(char **args)
{
    int i = 1;
    int newline = 1;

    if (args[1] && strcmp(args[1], "-n") == 0)
    {
        newline = 0;
        i = 2;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (newline)
        printf("\n");
        
    return SUCCESS;
}
