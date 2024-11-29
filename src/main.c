#include "minishell.h"

volatile sig_atomic_t g_signal = 0;
volatile sig_atomic_t g_in_child = 0;
volatile sig_atomic_t g_exit_status = 0;



int main(int argc, char * argv[], char ** envp)
{

    if(argv && argc > 1)
    {
        ft_putstr_fd("Minishell doesn't take arguments\n",STDOUT_FILENO);
        return (EXIT_FAILURE); 
    }
    char        *input;
    t_command   *cmd;
    int         status;

    init_signals();
    status = SUCCESS1;
    while (1)
    {
        input = read_input();
        if (!input)
        {
            printf("exit\n");
            break;
        }
        if (strlen(input) > 0)
            add_history(input);
        cmd = parse_input(input);
        
        
        free(input);
        if (!cmd)
        {
            continue;
        }
        g_exit_status = execute_commands(cmd,init_minienv(envp));
        free_commands(cmd);
        if (g_exit_status == EXIT_SHELL)
            return(g_exit_status);
        // Reset signal flags
        if (g_signal)
            g_signal = 0;
    }
    rl_clear_history();
    return (g_exit_status);
}


// int main()
// {

//     t_command * temp = NULL;
//     char * str = "ls | echo";
//     temp = parse_input(str);
//     while(temp)
//     {
//         char ** args = temp->args;
//         char * input_redir = temp->input_redir;
//         char * output_redir = temp->output_redir;
//         temp = temp->next;
//     }
        


// }
