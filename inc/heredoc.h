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
void	save_to_file(t_minishell *mshell, char *input, int fd, t_expand expand);
int		is_valid_char_expansion(char c);
void	next_tmp_file(char *file, int nb);

void	delete_tmp_files(t_arena **arena);
void	cleanup_in_heredoc(t_arena **arena, char **input, int fd_stdin);
void	print_warning(char *eof);
int		is_eof(char *eof, char *input);

#endif
