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

int	open_redir_file(const char *file, int flags, int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	*fd = open(file, flags, 0644);
	if (*fd < 0)
	{
		ft_dprintf(2, "Giraffeshell: %s: %s\n", file, strerror(errno));
		return (FAIL);
	}
	return (SUCCESS);
}

