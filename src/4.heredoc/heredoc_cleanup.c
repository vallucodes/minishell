/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:45:41 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 22:27:42 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	delete_tmp_files(t_minishell *mshell)
{
	size_t	i;
	char	*tmp_file;

	tmp_file = arena_alloc(mshell->arena, NAME_MAX + 1, alignof(char));
	if (!tmp_file)
		exit_cleanup_error(mshell, "malloc");
	i = 1;
	ft_bzero(tmp_file, NAME_MAX + 1);
	while (1)
	{
		next_tmp_file(mshell, tmp_file, i);
		if (access(tmp_file, F_OK) == 0)
		{
			if (unlink(tmp_file) == -1)
				perror("unlink");
			i++;
		}
		else
			break ;
	}
}

void	cleanup_at_signal(t_minishell *mshell, char **input,
	int fd_stdin, int fd_tmp)
{
	sig_action_ignore(mshell);
	if (close(fd_tmp) == -1)
		perror("close");
	delete_tmp_files(mshell);
	free(*input);
	if (dup2(fd_stdin, STDIN_FILENO) == -1)
		exit_cleanup_error(mshell, "dup2");
	if (close(fd_stdin) == -1)
		perror("close");
	free(mshell->input_str);
	arena_delete(&mshell->arena);
}

void	print_warning(size_t rl_count, char *eof)
{
	ft_dprintf(1, "giraffeshell: warning: here-document at line %u ", rl_count);
	ft_dprintf(1, "delimited by end-of-file (wanted `%s')\n", eof);
}

void	cleanup_at_success(t_minishell *mshell, char **input,
			int *fd_tmp, int *fd_stdin)
{
	sig_action_ignore(mshell);
	mshell->rl_count += mshell->rl_count_heredoc;
	mshell->rl_count_heredoc = 0;
	close_fds(fd_tmp, fd_stdin);
	free_and_set(input);
}
