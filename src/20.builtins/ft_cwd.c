#include "../../inc/minishell.h"

int	get_current_directory(char *buffer, size_t size)
{
	if (!getcwd(buffer, size))
	{
		ft_dprintf(STDERR_FILENO,
			"cd: error retrieving current directory: getcwd: cannot access parent directories: %s\n",
			strerror(errno));
		return (FAIL);
	}
	return (SUCCESS);
}
