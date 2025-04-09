#include "../../inc/minishell.h"

int ft_env(t_env **my_env, char **ast_cmd)
{
    unsigned int	i;
    int				arg_count;

    if (!my_env || !(*my_env) || !(*my_env)->envp)
        return (FAIL);

    arg_count = count_cmds(&ast_cmd[1]); //skip env, start from arg
    if (arg_count > 0)
    {
        ft_dprintf(STDERR_FILENO, "minishell: env: too many arguments\n");
        return (1);
    }
    i = 0;
    while (i < (*my_env)->len)
    {
        if ((*my_env)->envp[i] && ft_strchr((*my_env)->envp[i], '='))
            printf("%s\n", (*my_env)->envp[i]);
        i++;
    }

    return (0);
}

