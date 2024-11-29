#include "builtins.h"
#include "minishell.h"

int	execute_builtin(t_command *cmd)
{
	if (strcmp(cmd->args[0], "cd") == 0)
		return (builtin_cd(cmd->args));
	else if (strcmp(cmd->args[0], "echo") == 0)
		return (builtin_echo(cmd->args));
	else if (strcmp(cmd->args[0], "env") == 0)
		return (builtin_env(cmd->args));
	else if (strcmp(cmd->args[0], "exit") == 0)
		return (builtin_exit(cmd->args));
	else if (strcmp(cmd->args[0], "export") == 0)
		return (builtin_export(cmd->args));
	else if (strcmp(cmd->args[0], "pwd") == 0)
		return (builtin_pwd(cmd->args));
	else if (strcmp(cmd->args[0], "unset") == 0)
		return (builtin_unset(cmd->args));
	return (SUCCESS);
}
