#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"



# include <stdio.h> // perror
# include <readline/readline.h> // readline
# include <readline/history.h> // history
# include <stdlib.h> // getenv
# include <unistd.h> // getpwd
# include <sys/wait.h> // waitpid
# include <sys/stat.h> // stat
# include <signal.h> // sigaction
# include <fcntl.h> // open flags

typedef struct s_command	t_command;
typedef struct s_env        t_env;

char						*read_input(void);
void						error_handling(const char *msg);
void						free_args(char **args);
char						*str_join(char *s1, char *s2);
int							is_metachar(char c);
char						*get_env_value(const char *name);
char						*expand_env_vars(const char *str);
void						free_commands(t_command *cmd);
int							is_valid_identifier(const char *str);
t_env	                    *init_minienv(char **envp);
void	                    list_append(char *key_pair, t_env **list);
int	                        has_pipe(char *str);
void	save_original_fd_in(int original_fds[2]);
void	save_original_fd_out(int original_fds[2]);
int	handle_input_redirect(char * cmd, int original_fds[2]);
int	handle_output_redirect(char * cmd, int original_fds[2]);
int	redirect_output(char *command);
void	redirect_fd(int fd_to_redirect, int fd_location);
char	*get_label_name(char *redirect_str);
void	move_one_forward(char *str);
int	is_empty(char *str);
int	is_quote(char c);
int	is_name_delimeter(char c);
int	                        redirect_input(char * cmd);
char	*get_redirect_position(char *cmd, char redirect_char);
int	str_equal(const char *str1, const char *str2);




char	*get_path(char *command, t_env *minienv);
char	*minienv_value(char *name, t_env *minienv);
char	**minienv_to_envp(t_env *minienv);
size_t	minienv_size(t_env *minienv);
int	execute_forked_external(char **args, t_env *minienv);
void	free_minienv(t_env **minienv);
t_env	*minienv_node(char *name, t_env *minienv);
char	*value_only(char *key_pair);
void	free_array(char **arr);
int	wait_for_child(int child_pid, int is_last_child);
void	redirect_heredoc(char *command, int heredoc_number);
int	arr_len(char **arr);

char	**split_args(char *command);
void	close_extra_fds(void);
void	close_all_fds(void);
char * join_str(char ** strs);
int	*init_children_pid(char **commands);
void	clean_after_execute(int *children_pid);
void	quit_child(char **commands, t_env **minienv);
void	handle_pipe(int original_fd_out, char *current_command, char **commands);
int	wait_for_children(int children_pid[1024]);
int	execute_forked_builtin(char **args, t_env **minienv);

#endif
