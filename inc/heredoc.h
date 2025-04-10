#ifndef HEREDOC_H
# define HEREDOC_H

typedef enum e_expand
{
	DONT_EXPAND,
	EXPAND,
}	t_expand;


//heredoc
void	handle_heredoc(t_arena **arena, t_minishell mshell, t_token *tokens);
char	*create_tmp_file(t_arena **arena, int *fd);
void	save_to_file(t_minishell mshell, char *input, int fd, t_expand expand);
int		is_valid_char_expansion(char c);

#endif
