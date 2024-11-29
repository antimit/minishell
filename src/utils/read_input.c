#include "utils.h"

char	*read_input(void)
{
	char	*input;

	input = readline("minishell$> ");
	    unsetenv("COLUMNS");

    unsetenv("LINE");

	return (input);
}
