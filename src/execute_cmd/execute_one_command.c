
#include "minishell.h"






static int	handle_redirects(char *command, int original_fds[2])
{
	char	redirect;
	
	original_fds[IN] = NO_REDIRECT;
	original_fds[OUT] = NO_REDIRECT;
	redirect = get_next_redirect(command);
	
	

	while (redirect)
	{
		
		if (redirect == '<')
		{
			
			if (!handle_input_redirect(command, original_fds))
			{
				return (FAILED);
			}
				
		}
		
		if (redirect == '>')
		{
			
			return (FAILED);
		}
		if (redirect < 0)
		{
			save_original_fd_in(original_fds);
			redirect_heredoc(command, redirect);
		}
		redirect = get_next_redirect(command);
	}
	
	return (SUCCESS);
}

static void	restore_original_fds(int original_fds[2])
{
	if (original_fds[IN] != NO_REDIRECT)
		redirect_fd(original_fds[IN], STDIN_FILENO);
	if (original_fds[OUT] != NO_REDIRECT)
		redirect_fd(original_fds[OUT], STDOUT_FILENO);
}


int	execute_forked_external(char **args, t_env *minienv)
{
	
	int		child_pid;
	char	*command;
	
	command = args[0];
	child_pid = fork();
	define_execute_signals(child_pid);
	if (child_pid == -1)
		print_perror_msg("fork", command);
	else if (child_pid == 0)
	{
		
		execute_external(args, minienv);
	}
		
	else
	{

		return (wait_for_child(child_pid, TRUE));
	}
		
	exit(EXIT_FAILURE);
}


char * join_str(char ** strs)
{
	int i;
	int j;
	i = 0;
	int total_length = 0;
	while(strs[i])
	{
		total_length+=ft_strlen(strs[i]);
		i++;
	}
	total_length += (i -1);
	char * result = malloc(total_length +1);
	i = 0;
	int pos;
	pos = 0;
	while(strs[i])
	{
		strcpy(result + pos,strs[i]);
		pos += ft_strlen(strs[i]);


		if(strs[i+1])
		{
			result[pos]	= ' ';
			pos++;
		}
		i++;
	}
	result[pos] = '\0';
	return result;
}


int execute_one_command(t_command * cmd, t_env ** minienv)
{
	
    char ** args;
    int		exit_status;
	int		original_fds[2];

    char * command = join_str(cmd->args);

    if(!handle_redirects(command,&original_fds[0]))
    {
		restore_original_fds(original_fds);
		free(command);
        return (EXIT_FAILURE);
    }
	args = split_args(command);


	free(command);
	if(is_builtin(args[0]))
		exit_status = execute_builtin(args);
	else 
		exit_status = execute_forked_external(args, *minienv);
	free_array(args);
	restore_original_fds(original_fds);
	return exit_status;
	

}