#include "error.h"

int parsing_error(t_env_list *env, char *msg, int status)
{
	printf("minishell: %s\n", msg);
    free(env->value);
    env->value = ft_itoa(status);
	return (status);
}

void *parsing_error_return_null(t_env_list *env, char *msg, int status)
{
    printf("minishell: %s\n", msg);
    free(env->value);
    env->value = ft_itoa(status);
	return (NULL);
}