#include "builtins.h"
#include "utils.h" // Для is_valid_identifier
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int builtin_export(char **args)
{
    int i;
    char *name;
    char *value;
    char *equal;
    int status = SUCCESS1;

    if (!args[1])
        return (builtin_env(args)); // Если нет аргументов, вывести окружение

    i = 1;
    while (args[i])
    {
        equal = strchr(args[i], '=');
        if (equal)
        {
            *equal = '\0';
            name = args[i];
            value = equal + 1;

            if (!is_valid_identifier(name))
            {
                fprintf(stderr,
                    "minishell: export: `%s': not a valid identifier\n", name);
                status = 1;
            }
            else
            {
                if (setenv(name, value, 1) != 0)
                {
                    perror("minishell");
                    status = 1;
                }
            }
            *equal = '=';
        }
        else
        {
            name = args[i];
            if (!is_valid_identifier(name))
            {
                fprintf(stderr,
                    "minishell: export: `%s': not a valid identifier\n", name);
                status = 1;
            }
            else
            {
                // Проверяем, существует ли переменная
                if (getenv(name) == NULL)
                {
                    // Если нет, создаём её с пустым значением
                    if (setenv(name, "", 1) != 0)
                    {
                        perror("minishell");
                        status = 1;
                    }
                }
                // Если существует, ничего не делаем, переменная уже экспортирована
            }
        }
        i++;
    }
    return (status);
}


