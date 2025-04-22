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
    ft_dprintf(STDERR_FILENO,
		"pwd: error retrieving current directory: getcwd: cannot access parent directories: %s\n",
		strerror(errno));
    return (FAIL);
}
