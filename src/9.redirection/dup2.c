#include "../../inc/minishell.h"

int	safe_dup2(int fd, int target_fd)
{
	if (dup2(fd, target_fd) < 0)
	{
		perror("dup2");
		close(fd);
		return (FAIL);
	}
	return (SUCCESS);
}
