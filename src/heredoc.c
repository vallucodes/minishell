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

int	check_quotes(t_token *current)
{
	t_quotes_helper	quotes;
	char			*new_str;
	char			*input_str;
	size_t			i;
	char			expansion_flag;

	i = 0;
	expansion_flag = EXPAND;
	input_str = current->value;
	init_quotes(&quotes);
	new_str = ft_strdup("");
	while (input_str[i])
	{
		update_quote_state(input_str[i], &quotes);
		if (quotes.in_quotes)
			expansion_flag = DONT_EXPAND;
		if (is_quote_state_change(quotes))
		{
			i++;
			continue ;
		}
		append_char(input_str, &new_str, i);
		i++;
	}
	replace_content_of_token(current, new_str);
	return (expansion_flag);
}

void	handle_heredoc(t_arena **arena, char **env, t_token *tokens)
{
	t_token		*current;
	char		*file;
	t_expand	expansion_flag;

	expansion_flag = EXPAND;
	current = tokens;
	while (current)
	{
		if (current->type == HERE_DOCUMENT)
		{
			expansion_flag = check_quotes(current->next);
			file = read_line(arena, env, current->next->value, expansion_flag);
			replace_token(current, file);
		}
		current = current->next;
	}
}
