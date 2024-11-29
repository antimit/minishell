#include "minishell.h"

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_commands(t_command *cmd)
{
	t_command	*temp;

	while (cmd)
	{
		temp = cmd;
		cmd = cmd->next;
		free_args(temp->args);
		if (temp->input_redir)
			free(temp->input_redir);
		if (temp->output_redir)
			free(temp->output_redir);
		free(temp);
	}
}
