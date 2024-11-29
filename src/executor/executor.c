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


static int	execute_builtin_parent(t_command *cmd)
{
	int	status;

	
	g_in_child = 1;
	status = execute_builtin(cmd);
	
	g_in_child = 0;
   if (status == EXIT_SHELL)
        return (EXIT_SHELL);
    else
        g_exit_status = status;
	return (status);
}


int   execute_commands(t_command * cmd, t_env * envp)
{
	int exit_status;

	if(!cmd->next)
	{
		exit_status = execute_one_command(cmd, &envp);
	}
	return exit_status;
	
	
}

// int execute_commands(t_command *cmd)
// {
// 	int			fd[2];
// 	pid_t		pid;
// 	t_command	*current;
// 	int			prev_fd = -1;
// 	int			status = SUCCESS;
// 	pid_t		last_pid = -1; 
// 	pid_t		pids[100]; 
// 	int			pid_count = 0;

// 	current = cmd;
// 	while (current)
// 	{
		
// 		if (is_builtin_command(current) && !current->next)
// 		{
			
// 			status = execute_builtin_parent(current);
// 			if (status == EXIT_SHELL)
// 				return (EXIT_SHELL);
// 			break;
// 		}

		
// 		if (current->next)
// 		{
// 			if (pipe(fd) == -1)
// 			{
// 				perror("pipe");
// 				return (SUCCESS);
// 			}
// 		}

// 		pid = fork();
// 		if (pid == 0)
// 		{
			

			
// 			restore_default_signals();

			
// 			if (prev_fd != -1)
// 			{
// 				if (dup2(prev_fd, STDIN_FILENO) == -1)
// 				{
// 					perror("dup2");
// 					exit(EXIT_FAILURE);
// 				}
// 				close(prev_fd);
// 			}

			
// 			if (current->next)
// 			{
// 				if (dup2(fd[1], STDOUT_FILENO) == -1)
// 				{
// 					perror("dup2");
// 					exit(EXIT_FAILURE);
// 				}
// 				close(fd[0]);
// 				close(fd[1]);
// 			}

			
// 			if (handle_redirections(current) == -1)
// 				exit(EXIT_FAILURE);

			
// 			if (is_builtin_command(current))
// 			{
				
// 				execute_builtin(current);
// 				exit(g_exit_status);
// 			}
// 			else
// 			{
				
// 				if (execvp(current->args[0], current->args) == -1)
// 				{
// 					perror("minishell");
// 					exit(EXIT_FAILURE);
// 				}
// 			}
// 		}
// 		else if (pid < 0)
// 		{
			
// 			perror("fork");
// 			return (SUCCESS);
// 		}
// 		else
// 		{
			

			
// 			if (pid_count < 100)
// 				pids[pid_count++] = pid;
// 			else
// 			{
// 				fprintf(stderr, "Too many child processes\n");
// 				break;
// 			}

			
// 			if (prev_fd != -1)
// 				close(prev_fd);
// 			if (current->next)
// 			{
// 				close(fd[1]);
// 				prev_fd = fd[0];
// 			}
// 			else
// 			{
// 				prev_fd = -1;
// 			}

			
// 			current = current->next;
// 		}
// 	}

	
// 	if (prev_fd != -1)
// 		close(prev_fd);

	
// 	int	exit_status = 0;
// 	int	wstatus;
// 	pid_t	wpid;

// 	for (int i = 0; i < pid_count; i++)
// 	{
// 		wpid = waitpid(pids[i], &wstatus, 0);
// 		if (wpid == -1)
// 		{
// 			perror("waitpid");
// 			continue;
// 		}
// 		if (wpid == pids[pid_count - 1])
// 		{
// 			if (WIFEXITED(wstatus))
// 				exit_status = WEXITSTATUS(wstatus);
// 			else if (WIFSIGNALED(wstatus))
// 				exit_status = 128 + WTERMSIG(wstatus);
// 			else
// 				exit_status = wstatus;
// 		}
// 	}

// 	g_exit_status = exit_status;
// 	return (status);
// }