#ifndef HEREDOC_H
# define HEREDOC_H

typedef enum e_expand
{
	DONT_EXPAND,
	EXPAND,
}	t_expand;

//heredoc
int		handle_heredoc(t_minishell *mshell, t_token *tokens);
char	*create_tmp_file(t_minishell *mshell, int *fd);
void	save_line_to_tmp_file(t_minishell *mshell,
			char *input, int fd, t_expand expand);
int		is_valid_char_expansion(char c);
void	next_tmp_file(t_minishell *mshell, char *file, int nb);

//utils
void	print_warning(size_t readline_count, char *eof);
int		is_eof(char *eof, char *input);
int		get_stdin(t_minishell *mshell);

//cleanup and exit
void	delete_tmp_files(t_minishell *mshell);
void	cleanup_at_signal(t_minishell *mshell,
			char **input, int fd_stdin, int fd);
void	cleanup_at_success(t_minishell *mshell,
			char **input, int *fd_tmp, int *fd_stdin);
void	free_and_set(char **input);
void	close_fds(int *fd1, int *fd2);

#endif
