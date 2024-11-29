#include "minishell.h"

char get_next_redirect(t_command *cmd)
{
    int i = 0;
    char *str;

    while (cmd->args[i])
    {
        str = cmd->args[i];

        while (*str)
        {
            if (*str == '\'') // Handle single quotes
            {
                str++; // Skip opening quote
                while (*str && *str != '\'') // Skip until closing quote
                    str++;
                if (*str) // Skip closing quote
                    str++;
            }
            else if (*str == '"') // Handle double quotes
            {
                str++; // Skip opening quote
                while (*str && *str != '"') // Skip until closing quote
                    str++;
                if (*str) // Skip closing quote
                    str++;
            }
            else if (*str == '<' || *str == '>') // Found a redirect symbol
            {
                return *str;
            }
            else
            {
                str++; // Move to the next character
            }
        }
        i++;
    }
    return 0; // No redirect character found
}


char	*get_redirect_position(t_command * cmd, char redirect_char)
{
    // t_command * current = cmd;
    // while()
	// while (*str)
	// {
	// 	if (*str == '\'')
	// 	{
	// 		str++;
	// 		while (*str != '\'')
	// 			str++;
	// 	}
	// 	if (*str == '"')
	// 	{
	// 		str++;
	// 		while (*str != '"')
	// 			str++;
	// 	}
	// 	if (*str == redirect_char)
	// 		return (str);
	// 	str++;
	// }
	// return (NULL);
}


void	redirect_fd(int fd_to_redirect, int fd_location)
{
	dup2(fd_to_redirect, fd_location);
	close(fd_to_redirect);
}
