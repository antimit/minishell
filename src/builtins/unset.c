#include "builtins.h"

int builtin_unset(char **args)
{
	int		i;
	int		status = SUCCESS;

	if (!args[1])
	{
		
		return (SUCCESS);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			fprintf(stderr,
				"minishell: unset: `%s': not a valid identifier\n", args[i]);
			status = 1;
		}
		else
		{
			if (unsetenv(args[i]) != 0)
			{
				perror("minishell");
				status = 1;
			}
		}
		i++;
	}
	return (status);
}
