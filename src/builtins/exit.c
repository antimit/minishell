#include "builtins.h"
#include "minishell.h" // Для доступа к g_exit_status
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int builtin_exit(char **args)
{
    if (args[1] == NULL)
    {
        // Выход без аргументов: использовать текущий код выхода
        return EXIT_SHELL;
    }
    else
    {
        char *arg = args[1];
        char *endptr;
        long exit_code = strtol(arg, &endptr, 10);
		//printf("exit_code: %ld\n", exit_code);
        if (*endptr != '\0')
        {
            // Аргумент не является числом
            fprintf(stderr, "minishell: exit: %s: numeric argument required\n", arg);
            g_exit_status = 2;
            return EXIT_SHELL;
        }
        else
        {
            if (args[2] != NULL)
            {
                // Слишком много аргументов
                fprintf(stderr, "minishell: exit: too many arguments\n");
                g_exit_status = 1;
                return EXIT_SHELL; // Не выходить из шелла
            }
            else
            {
                // Корректный аргумент: устанавливаем код выхода
                g_exit_status = (int)(exit_code % 256);
                return EXIT_SHELL;
            }
        }
    }
}
