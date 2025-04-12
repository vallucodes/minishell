#include "../../inc/minishell.h"

int safe_open_redirect(int *redir_fd, char *filepath, int flags, int mode)
{
	//close can happen

	if (*redir_fd != STDIN_FILENO && *redir_fd != STDOUT_FILENO )
		close(*redir_fd);

	*redir_fd = open(filepath, flags, mode);
	if (*redir_fd == -1)
	{
		perror(filepath);
		return(FAIL);
	}
	return SUCCESS;
}
