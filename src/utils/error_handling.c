#include "utils.h"

void	error_handling(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
