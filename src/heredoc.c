#include "../inc/minishell.h"

static char	*read_line(t_arena **arena, char **env, char *eof, t_expand expand)
{
	char	*input;
	int		fd;
	char	*file;

	file = create_tmp_file(arena, &fd);
	input = readline("> ");
	while (ft_strncmp(eof, input, ft_strlen(eof)) || (ft_strlen(input) != ft_strlen(eof)))
	{
		save_to_file(env, input, fd, expand);
		free(input);
		input = NULL;
		input = readline("> ");
	}
	free(input);
	input = NULL;
	return (file);
}

static void	replace_token(t_token *current, char *file)
{
	current->value++;
	current->len = 1;
	current->type = REDIRECT_IN;
	current->next->type = FILE_TOKEN;
	current->next->value = file;
	current->next->len = ft_strlen(file);
}

void	handle_heredoc(t_arena **arena, char **env, t_token *tokens)
{
	t_token *current;
	char	*file;


	current = tokens;
	while (current)
	{
		if (current->type == HERE_STRING)
		{
			file = read_line(arena, env, current->next->value, EXPAND);
			replace_token(current, file);
		}
		current = current->next;
	}
}
