#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>

int builtin_env(char **args)
{
    extern char **environ; // Глобальная переменная окружения
    int i = 0;

    (void)args; // Параметр args не используется

    while (environ[i])
    {
        printf("%s\n", environ[i]); // Вывод каждой переменной на новой строке
        i++;
    }

    g_exit_status = 0; // Устанавливаем статус выполнения
    return (SUCCESS);
}
