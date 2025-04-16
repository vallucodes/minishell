#include "../inc/minishell.h"

void	delete_tmp_files(t_arena **arena)
{
	size_t	i;
	char	*tmp_file;

	tmp_file = arena_alloc(*arena, NAME_MAX + 1, alignof(char));
	// if (!tmp_file)
		// exit_cleanup_error(mshell, "malloc");
	i = 1;
	ft_bzero(tmp_file, NAME_MAX + 1);
	while (1)
	{
		next_tmp_file(tmp_file, i);
		if (access(tmp_file, F_OK) == 0)
		{
			unlink(tmp_file);
			i++;
		}
		else
			break ;
	}
}

void	cleanup_in_heredoc(t_arena **arena, char **input, int fd_stdin)
{
	delete_tmp_files(arena);
	free(*input);
	dup2(fd_stdin, STDIN_FILENO);
	close(fd_stdin);
	arena_destroy(arena);
}

void	print_warning(char *eof)
{
	ft_dprintf(1, "giraffeshell: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n", eof); // add proper counter, counts amount of inputs from every readline call
}
