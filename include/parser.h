
#ifndef PARSER_H
#define PARSER_H
# include "minishell.h"
typedef enum {
    TOKEN_NONE,
    TOKEN_SINGLE_QUOTE,
    TOKEN_DOUBLE_QUOTE
} token_quote;

typedef struct s_token {
    char *value;
    token_quote quote;
    struct s_token *next;
} t_token;

typedef struct s_command	t_command;

// Объявления функций
t_command *parse_input(char *input);
t_token *tokenize_input(const char *input);
void free_tokens(t_token *tokens);
void						find_redirections(t_command *cmd);
void						remove_args(char **args, int index, int count);
t_command *create_command(char **args);
void						append_command(t_command *head, t_command *new_cmd);
#endif // PARSER_H
