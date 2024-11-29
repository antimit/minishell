#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	init_signals(void);
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void ignore_signals(void); 
void restore_default_signals(void);
void restore_custom_signals(void);
void	define_execute_signals(int child_pid);
#endif
