#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"
typedef struct s_command	t_command;

int							execute_builtin(char ** cmd);
int	                        is_builtin(char *command);
int							builtin_cd(char **args);
int							builtin_echo(char **args);
int							builtin_env(char **args);
int							builtin_exit(char **args);
int							builtin_export(char **args);
int							builtin_pwd(char **args);
int							builtin_unset(char **args);

#endif
