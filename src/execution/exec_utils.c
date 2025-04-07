#include "../../inc/minishell.h"

int safe_open_redirect(const char *filepath, int flags, int mode)
{
	int fd = open(filepath, flags, mode);
	if (fd == -1)
		perror(filepath);
	return fd;
}
