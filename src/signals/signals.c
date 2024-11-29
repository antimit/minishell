// signals.c

#include "signals.h"
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


/**
 * Обработчик для SIGINT (Ctrl+C)
 */
void handle_sigint(int sig)
{
    (void)sig; // Подавление предупреждения об неиспользуемом параметре

   
        // Вывод "^C\n" в терминал
        write(STDOUT_FILENO, "^C\n",3);
        // Очистка текущей строки ввода
        rl_replace_line("", 0);
        // Перевод курсора на новую строку
        rl_on_new_line();
        // Повторное отображение приглашения
        rl_redisplay();  
   

    // Если в дочернем процессе, ничего не делаем (дочерний процесс имеет стандартный обработчик)
}

/**
 * Обработчик для SIGQUIT (Ctrl+\)
 */
void handle_sigquit(int sig)
{
    (void)sig; // Подавление предупреждения об неиспользуемом параметре

    if (!g_in_child)
    {
        // Игнорируем SIGQUIT в родительском процессе
        write(STDOUT_FILENO, "Quit: 3\n", 8);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    // Если в дочернем процессе, ничего не делаем (дочерний процесс имеет стандартный обработчик)
}

/**
 * Инициализация пользовательских обработчиков сигналов
 */
void init_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    // Настройка обработчика SIGINT
    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sa_int, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Настройка обработчика SIGQUIT
    sa_quit.sa_handler = handle_sigquit;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;
    if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

/**
 * Игнорирование SIGINT и SIGQUIT сигналов
 */
void ignore_signals(void)
{
    struct sigaction sa_ignore;

    sa_ignore.sa_handler = SIG_IGN;
    sigemptyset(&sa_ignore.sa_mask);
    sa_ignore.sa_flags = 0;

    if (sigaction(SIGINT, &sa_ignore, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGQUIT, &sa_ignore, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

/**
 * Восстановление пользовательских обработчиков сигналов
 */
void restore_custom_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    // Восстанавливаем обработчик SIGINT
    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    if (sigaction(SIGINT, &sa_int, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Восстанавливаем обработчик SIGQUIT
    sa_quit.sa_handler = handle_sigquit;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;
    if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

/**
 * Восстановление стандартных обработчиков сигналов (для дочерних процессов)
 */
void restore_default_signals(void)
{
    struct sigaction sa_default;

    sa_default.sa_handler = SIG_DFL;
    sigemptyset(&sa_default.sa_mask);
    sa_default.sa_flags = 0;

    if (sigaction(SIGINT, &sa_default, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGQUIT, &sa_default, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}
