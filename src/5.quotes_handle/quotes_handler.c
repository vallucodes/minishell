#include "../inc/minishell.h"

static void	loop_through_word(char **env, int exitcode, t_token *current)
{
	t_quotes_helper	quotes;
	char			*new_str;
	char			*input_str;
	size_t			i;

	i = 0;
	input_str = current->value;
	new_str = ft_strdup("");
	init_quotes(&quotes);
	while (input_str[i])
	{
		update_quote_state(input_str[i], &quotes);
		if (is_valid_expandable(quotes, &input_str[i]))
			i += expand_content(env, &input_str[i], 0, &new_str);
		else if (is_pid_expansion(quotes, &input_str[i]))
			i += expand_pid(0, &new_str);
		else if (is_exitcode_expansion(quotes, &input_str[i]))
			i += expand_exitcode_value(exitcode, 0, &new_str);
		else if (there_is_quote_state_change(quotes))
			i++;
		else
			append_char(input_str, &new_str, i++);
	}
	replace_content_of_token(current, new_str);
}

void	expand_remove_quotes(char **env, int exitcode, t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current)
	{
		if (is_any_word(current->type))
			loop_through_word(env, exitcode, current);
		current = current->next;
	}
}
