

#include "parser.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


t_token *tokenize_input(const char *input)
{
    t_token *head = NULL;
    t_token *current = NULL;
    size_t i = 0;
    size_t len = strlen(input);
    char buffer[4096];
    size_t buf_index = 0;
    token_quote current_quote = TOKEN_NONE;

    while (i < len)
    {
        
        while (i < len && isspace(input[i]))
            i++;
        if (i >= len)
            break;

        buf_index = 0;

        
        while (i < len && !isspace(input[i]))
        {
            if (input[i] == '\'')
            {
                current_quote = TOKEN_SINGLE_QUOTE;
                i++; 
                while (i < len && input[i] != '\'')
                {
                    buffer[buf_index++] = input[i++];
                }
                if (i < len && input[i] == '\'')
                    i++; 
            }
            else if (input[i] == '\"')
            {
                current_quote = TOKEN_DOUBLE_QUOTE;
                i++; 
                while (i < len && input[i] != '\"')
                {
                    if (input[i] == '\\' && (i + 1) < len && 
                        (input[i+1] == '\"' || input[i+1] == '\\' || input[i+1] == '$' || input[i+1] == '`'))
                    {
                        buffer[buf_index++] = input[i+1];
                        i += 2;
                    }
                    else
                    {
                        buffer[buf_index++] = input[i++];
                    }
                }
                if (i < len && input[i] == '\"')
                    i++; 
            }
            else
            {
                buffer[buf_index++] = input[i++];
            }
        }

        buffer[buf_index] = '\0';

        
        char *processed_value = NULL;
        if (current_quote != TOKEN_SINGLE_QUOTE)
        {
            processed_value = expand_env_vars(buffer);
            if (!processed_value)
            {
                free_tokens(head);
                return NULL;
            }
        }
        else
        {
            processed_value = strdup(buffer);
            if (!processed_value)
            {
                free_tokens(head);
                return NULL;
            }
        }

        
        t_token *new_token = malloc(sizeof(t_token));
        if (!new_token)
        {
            free(processed_value);
            free_tokens(head);
            return NULL;
        }
        new_token->value = processed_value;
        new_token->quote = current_quote;
        new_token->next = NULL;

        
        if (!head)
        {
            head = new_token;
            current = new_token;
        }
        else
        {
            current->next = new_token;
            current = new_token;
        }

        
        current_quote = TOKEN_NONE;
    }

    return head;
}


void free_tokens(t_token *tokens)
{
    t_token *tmp;
    while (tokens)
    {
        tmp = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = tmp;
    }
}


t_command *create_command(char **args)
{
    t_command *cmd = malloc(sizeof(t_command));
    if (!cmd)
        return NULL;

    
    int count = 0;
    while (args[count])
        count++;

    
    cmd->args = malloc(sizeof(char*) * (count + 1));
    if (!cmd->args)
    {
        free(cmd);
        return NULL;
    }

    for (int i = 0; i < count; i++)
        cmd->args[i] = strdup(args[i]);
    cmd->args[count] = NULL;

    
    cmd->input_redir = NULL;
    cmd->output_redir = NULL;
    cmd->append = 0;    fflush(stdout);
    cmd->next = NULL;

    
    find_redirections(cmd);
    return cmd;
}


void append_command(t_command *head, t_command *new_cmd)
{
    t_command *temp = head;
    while (temp->next)
        temp = temp->next;
    temp->next = new_cmd;
}
void remove_args(char **args, int index, int count)
{
    int i = index;
    while (args[i + count])
    {
        free(args[i]); 
        args[i] = strdup(args[i + count]);
        i++;
    }
    while (args[i])
    {
        free(args[i]);
        args[i] = NULL;
        i++;
    }
}