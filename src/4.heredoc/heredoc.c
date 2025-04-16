#include "../inc/minishell.h"

static char	*read_line(t_minishell *mshell, char *eof, t_expand expand)
{
	char	*input;
	int		fd;
	char	*file;

	file = create_tmp_file(mshell, &fd);
	signal_action_heredoc(mshell->sa);
	while (1)
	{
		int	fd_stdin = dup(STDIN_FILENO);
		input = readline("> ");
		if (g_signal == SIGINT)
			return (cleanup_in_heredoc(&mshell->arena, &input, fd_stdin), NULL);
		if (!input)
		{
			print_warning(eof);
			break ;
		}
		if (is_eof(eof, input))
			break ;
		save_to_file(mshell, input, fd, expand);
		free(input);
		input = NULL;
	}
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

static int	check_quotes(t_minishell *mshell, t_token *current)
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
		if (there_is_quote_state_change(quotes))
		{
			i++;
			continue ;
		}
		append_char(mshell, input_str, &new_str, i);
		i++;
	}
	replace_content_of_token(current, new_str);
	return (expansion_flag);
}

int	handle_heredoc(t_minishell *mshell, t_token *tokens)
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
			expansion_flag = check_quotes(mshell, current->next);
			file = read_line(mshell, current->next->value, expansion_flag);
			if (file == NULL)
				return (FAIL);
			replace_token(current, file);
		}
		current = current->next;
	}
	return (SUCCESS);
}
