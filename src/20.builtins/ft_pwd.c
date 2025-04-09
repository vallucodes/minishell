#include "../../inc/minishell.h"

int ft_pwd(void)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        return (SUCCESS);
    }
    perror("pwd");
    return (FAIL);
}
