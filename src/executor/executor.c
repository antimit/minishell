#include "executor.h"
#include "signals.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "minishell.h"
static int	is_builtin_command(t_command *cmd)
{
	const char	*builtins[] = {"cd", "echo", "pwd", "export", "unset", "env", "exit"};
	int			i;

	if (!cmd->args || !cmd->args[0])
		return (0);
	i = 0;
	while (i < 7)
	{
		if (strcmp(cmd->args[0], builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}


// static int	execute_builtin_parent(t_command *cmd)
// {
// 	int	status;

	
// 	g_in_child = 1;
// 	status = execute_builtin(cmd);
	
// 	g_in_child = 0;
//    if (status == EXIT_SHELL)
//         return (EXIT_SHELL);
//     else
//         g_exit_status = status;
// 	return (status);
// }


static char ** create_commands(t_command * cmd)
{
	char ** result;
	int count;
	char * str;
	t_command * temp;
	temp = cmd;
	count = 0;
	while(temp)
	{
		count++;
		temp = temp->next;
	}

	result = malloc(sizeof(char *) * count +1);
	temp = cmd;
	count = 0;
	while(temp)
	{
		str = join_str(temp->args);
		char * arg = ft_strdup(str);
		result[count] = arg;
		count++;
		temp = temp->next;
	}
	result[count] = '\0';
	return result;
}

int   execute_commands(t_command * cmd, t_env * envp)
{
	int exit_status;
	char ** args = cmd->args;
	char ** commands;
		
	int i;
	i = 0;
	if(!cmd->next)
	{		
		exit_status = execute_one_command(cmd, &envp);
	}
	else
	{
		char ** result = create_commands(cmd);
		exit_status = execute_multiple_commands(commands, &envp);
		free_array(result);
		
	}
	// else
	// {
	// 	commands = split_commands(input);	
	// 	exit_status = execute_multiple_commands(commands, &minienv);
	// }
	return exit_status;
	
	
}

