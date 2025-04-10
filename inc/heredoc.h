#ifndef HEREDOC_H
# define HEREDOC_H

typedef enum e_expand
{
	DONT_EXPAND,
	EXPAND,
}	t_expand;


//heredoc
void	handle_heredoc(t_arena **arena, char **env, t_token *tokens);
char	*create_tmp_file(t_arena **arena, int *fd);
void	save_to_file(char **env, char *input, int fd, t_expand expand);
int		is_valid_char_expansion(char c);

#endif
