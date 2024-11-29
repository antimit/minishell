#include "minishell.h"

int	handle_heredoc(t_command *cmd, const char *delimiter)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	return (0);
}

// int	handle_redirections(t_command *cmd)
// {
// 	int	fd;

// 	if (cmd->input_redir)
// 	{
// 		if (strncmp(cmd->input_redir, "<<", 2) == 0)
// 		{
// 			if (handle_heredoc(cmd, cmd->input_redir + 2) == -1)
// 				return (-1);
// 		}
// 		else
// 		{
// 			fd = open(cmd->input_redir, O_RDONLY);
// 			if (fd < 0)
// 				return (perror(cmd->input_redir), -1);
// 			dup2(fd, STDIN_FILENO);
// 			close(fd);
// 		}
// 	}
// 	if (cmd->output_redir)
// 	{
// 		if (cmd->append)
// 			fd = open(cmd->output_redir, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 		else
// 			fd = open(cmd->output_redir, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		if (fd < 0)
// 			return (perror(cmd->output_redir), -1);
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 	}
// 	return (0);
// }
