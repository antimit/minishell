#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
typedef struct s_env t_env;
typedef struct s_command	t_command;

int         execute_commands(t_command * cmd, t_env * envp);
char	get_next_redirect(t_command * cmd);
int execute_one_command(t_command * cmd, t_env ** minienv);
int	execute_external(char **args, t_env *minienv);


#endif
