#include "builtins.h"
#include "minishell.h"


int	execute_forked_builtin(char **args, t_env **minienv)
{
	int	exit_status;

	exit_status = execute_builtin(args);
	free_array(args);
	free_minienv(minienv);
	rl_clear_history();
	exit(exit_status);
}

int	execute_builtin(char  **args)
{
	if (strcmp(args[0], "cd") == 0)
		return (builtin_cd(args));
	else if (strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	else if (strcmp(args[0], "env") == 0)
		return (builtin_env(args));
	else if (strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	else if (strcmp(args[0], "export") == 0)
		return (builtin_export(args));
	else if (strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(args));
	else if (strcmp(args[0], "unset") == 0)
		return (builtin_unset(args));
	return (SUCCESS1);
}
