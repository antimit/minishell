#include "parser.h"

static char	*handle_quotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	result = malloc(strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && !quote)
			quote = str[i++];
		else if (str[i] == quote)
		{
			quote = 0;
			i++;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void find_redirections(t_command *cmd)
{
    int i = 0;
    while (cmd->args[i])
    {
        if (strcmp(cmd->args[i], "<") == 0)
        {
            if (cmd->args[i + 1])
            {
                cmd->input_redir = strdup(cmd->args[i + 1]);
                remove_args(cmd->args, i, 2);
            }
            else
            {
                
                i++;
            }
        }
        else if (strcmp(cmd->args[i], ">") == 0)
        {
            if (cmd->args[i + 1])
            {
                cmd->output_redir = strdup(cmd->args[i + 1]);
                cmd->append = 0;
                remove_args(cmd->args, i, 2);
            }
            else
            {
                i++;
            }
        }
        else if (strcmp(cmd->args[i], ">>") == 0)
        {
            if (cmd->args[i + 1])
            {
                cmd->output_redir = strdup(cmd->args[i + 1]);
                cmd->append = 1;
                remove_args(cmd->args, i, 2);
            }
            else
            {
                i++;
            }
        }
        else if (strcmp(cmd->args[i], "<<") == 0)
        {
            if (cmd->args[i + 1])
            {
                cmd->input_redir = strdup(cmd->args[i + 1]);
                remove_args(cmd->args, i, 2);
            }
            else
            {
                i++;
            }
        }
        else
        {
            i++;
        }
    }
}

t_command *parse_input(char *input)
{
    
    t_command *head = NULL;
    t_command *current_cmd = NULL;
    t_token *tokens = tokenize_input(input);
    t_token * current = tokens;
    // printf("Beginning\n");
    // while(current)
    // {
    //     printf("%s\n",current->value);
    //     current = current->next;
    // }
    // printf("End\n");
    t_token *token = tokens;
    char **args = NULL;
    int args_size = 0;
    int args_capacity = 10; 

    args = malloc(sizeof(char*) * args_capacity);
    if (!args)
    {
        free_tokens(tokens);
        return NULL;
    }   

    while (token)
    {
        if (strcmp(token->value, "|") == 0)
        {
            
            if (args_size == 0)
            {
                
                free(args);
                free_tokens(tokens);
                return NULL;
            }
            // printf("not skipped\n");
            args[args_size] = NULL; 
            t_command *new_cmd = create_command(args);
            if (!head)
                head = new_cmd;
            else
                append_command(head, new_cmd);

            
            args_size = 0;

            token = token->next;
            continue;
        }

        
        if (args_size >= args_capacity - 1)
        {
            args_capacity *= 2;
            char **temp = realloc(args, sizeof(char*) * args_capacity);
            if (!temp)
            {
                
                for (int i = 0; i < args_size; i++)
                    free(args[i]);
                free(args);
                free_tokens(tokens);
                return NULL;
            }
            args = temp;
        }

        args[args_size++] = strdup(token->value);
        token = token->next;
    }


    
    if (args_size > 0)
    {
        args[args_size] = NULL;
        t_command *new_cmd = create_command(args);
        if (!head)  
            head = new_cmd;
        else
            append_command(head, new_cmd);
    }

    

    free(args);
    free_tokens(tokens);
    return head;
}
