#include "../../inc/minishell.h"

#include <linux/limits.h>
int ft_pwd(void)
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("%s\n", cwd);
        return (SUCCESS);
    }
    perror("pwd");
    return (FAIL);
}
