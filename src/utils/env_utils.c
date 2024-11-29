

#include "utils.h"
#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

extern volatile sig_atomic_t g_exit_status;

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !(isalpha(str[0]) || str[0] == '_' || str[0]=='-'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (!(isalnum(str[i]) || str[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char *get_env_value(const char *name)
{
    char *value = getenv(name);
    if (value)
        return value;
    return "";
}

char *extract_var_name(char **str);

char *expand_env_vars(const char *str)
{
    char *result = malloc(1);
    if (!result)
        return NULL;
    result[0] = '\0';
    size_t len = 0;

    while (*str)
    {
        if (*str == '$')
        {
            str++;
            if (*str == '?')
            {
                
                str++;
                char exit_status_str[12];
                snprintf(exit_status_str, sizeof(exit_status_str), "%d", g_exit_status);
                size_t value_len = strlen(exit_status_str);
                char *temp = realloc(result, len + value_len + 1);
                if (!temp)
                {
                    free(result);
                    return NULL;
                }
                result = temp;
                strcat(result, exit_status_str);
                len += value_len;
            }
            else
            {
                
                char var_name[256];
                int i = 0;
                while (*str && (isalnum(*str) || *str == '_') && i < 255)
                {
                    var_name[i++] = *str;
                    str++;
                }
                var_name[i] = '\0';
                if (i == 0)
                {
                    
                    char *temp = realloc(result, len + 2);
                    if (!temp)
                    {
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    result[len++] = '$';
                    result[len] = '\0';
                }
                else
                {
                    char *value = get_env_value(var_name);
                    size_t value_len = strlen(value);
                    char *temp = realloc(result, len + value_len + 1);
                    if (!temp)
                    {
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    strcat(result, value);
                    len += value_len;
                }
            }
        }
        else
        {
            
            char *temp = realloc(result, len + 2);
            if (!temp)
            {
                free(result);
                return NULL;
            }
            result = temp;
            result[len++] = *str++;
            result[len] = '\0';
        }
    }

    return result;
}

char *extract_var_name(char **str)
{
    char var_name[256];
    int  i;

    i = 0;
    while (**str && (isalnum(**str) || **str == '_') && i < 255)
    {
        var_name[i++] = **str;
        (*str)++;
    }
    var_name[i] = '\0';
    return (strdup(var_name));
}


char	**minienv_to_envp(t_env *minienv)
{
	char	**envp;
	t_env	*aux;
	int		i;

	envp = malloc(sizeof(char *) * (minienv_size(minienv) + 1));
	aux = minienv;
	i = 0;
	while (aux)
	{
		envp[i] = ft_strdup(aux->key_pair);
		i++;
		aux = aux->next;
	}
	envp[i] = NULL;
	return (envp);
}


size_t	minienv_size(t_env *minienv)
{
	size_t	size;
	t_env	*aux;

	size = 0;
	aux = minienv;
	while (aux)
	{
		size++;
		aux = aux->next;
	}
	return (size);
}

