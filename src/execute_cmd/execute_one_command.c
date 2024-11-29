
#include "minishell.h"






static int	handle_redirects(t_command * cmd, int original_fds[2])
{
	char	redirect;

	original_fds[IN] = NO_REDIRECT;
	original_fds[OUT] = NO_REDIRECT;
	redirect = get_next_redirect(cmd);
	while (redirect)
	{
		if (redirect == '<')
		{
			if (!handle_input_redirect(cmd, original_fds))
				return (FAILED);
		}
		// if (redirect == '>')
		// {
		// 	if (!handle_output_redirect(command, original_fds))
		// 		return (FAILED);
		// }
		// if (redirect < 0)
		// {
		// 	save_original_fd_in(original_fds);
		// 	redirect_heredoc(command, redirect);
		// }
		redirect = get_next_redirect(cmd);
	}
	return (SUCCESS);
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
		execute_external(args, minienv);
	else
		return (wait_for_child(child_pid, TRUE));
	exit(EXIT_FAILURE);
}



int execute_one_command(t_command * cmd, t_env ** minienv)
{
    char ** args;
    int		exit_status;
	int		original_fds[2];

    
    // if(!handle_redirects(cmd,&original_fds[0]))
    // {
    //     return (EXIT_FAILURE);
    // }
	args = cmd->args;

	if(is_builtin(args[0]))
		exit_status = execute_builtin(cmd);
	else 
		exit_status = execute_forked_external(args, *minienv);
	return exit_status;
	

}