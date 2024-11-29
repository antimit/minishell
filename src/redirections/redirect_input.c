#include "minishell.h"


int	redirect_input(t_command * cmd)
{
	char	*input_redirect;
	char	*file_name;
	int		fd;
	input_redirect = get_redirect_position(cmd, '<');
	if (!input_redirect)
		return (SUCCESS);
	file_name = get_label_name(input_redirect);
	// printf("%s\n",file_name);
	fd = open(file_name, O_RDONLY, FD_CLOEXEC);
	if (fd == -1)
	{
		// print_perror_msg("open", file_name);
		free(file_name);
		return (FAILED);
	}
	else
		redirect_fd(fd, STDIN_FILENO);
	free(file_name);
	return (SUCCESS);
}
