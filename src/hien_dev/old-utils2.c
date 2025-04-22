#include "../../inc/minishell.h"

static int safe_close(int fd)
{
	if (fd < 0)
		return (SUCCESS);

	if (close(fd) == -1)
	{
		perror("close");
		return (FAIL);
	}
	return (SUCCESS);
}

static int safe_dup2(int src, int dest)
{
	if (dup2(src, dest) == -1)
	{
		perror("dup2");
		return (FAIL);
	}
	return (SUCCESS);
}

static int safe_dup(int target_fd, int *saved_fd)
{
	*saved_fd = dup(target_fd);
	if (*saved_fd == -1)
	{
		perror("dup");
		return (FAIL);
	}
	return (SUCCESS);
}

static int redirect_and_close(int src_fd, int target_fd)
{
	if (safe_dup2(src_fd, target_fd) == FAIL)
		return (FAIL);
	if (safe_close(src_fd) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int save_and_redirect_stdin(int new_fd, int *saved_stdin)
{
	if (new_fd == STDIN_FILENO)
		return (SUCCESS);

	if (safe_dup(STDIN_FILENO, saved_stdin) == FAIL)
		return (FAIL);

	if (redirect_and_close(new_fd, STDIN_FILENO) == FAIL)
	{
		safe_close(*saved_stdin);
		return (FAIL);
	}
	return (SUCCESS);
}

int save_and_redirect_stdout(int new_fd, int *saved_stdout)
{
	if (new_fd == STDOUT_FILENO)
		return (SUCCESS);

	if (safe_dup(STDOUT_FILENO, saved_stdout) == FAIL)
		return (FAIL);

	if (redirect_and_close(new_fd, STDOUT_FILENO) == FAIL)
	{
		safe_close(*saved_stdout);
		return (FAIL);
	}
	return (SUCCESS);
}

int restore_stdin(int saved_stdin)
{
    if (saved_stdin == -1)
        return (SUCCESS); // Nothing to restore

    if (safe_dup2(saved_stdin, STDIN_FILENO) == FAIL)
    {
        safe_close(saved_stdin);
        return (FAIL);
    }
    return safe_close(saved_stdin);
}


int restore_stdout(int saved_stdout)
{
	if (saved_stdout == -1)
		return (SUCCESS);

	if (safe_dup2(saved_stdout, STDOUT_FILENO) == FAIL)
	{
		safe_close(saved_stdout);
		return (FAIL);
	}
	return safe_close(saved_stdout);
}






