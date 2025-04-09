#include "../inc/minishell.h"

int	is_valid_expandable(t_quotes_helper quotes, char *input_str)
{
	int	i;

	i = 0;
	return (!quotes.in_single && input_str[i] == '$' &&
		is_valid_char_expansion(input_str[i + 1]));
}

int	there_is_quote_state_change(t_quotes_helper quotes)
{
	return (quotes.previous_in_quotes != quotes.in_quotes);
}

int	is_any_word(t_token_type type)
{
	return ((type == COMMAND) || (type == ARG) || (type == FILE_TOKEN));
}

int	expandable_exists(int len, char **env, int i, char *str)
{
	return ((ft_strncmp(&env[i][0], &str[1], len - 1) == 0) &&
		(env[i][len - 1] == '='));
}

void	replace_content_of_token(t_token *current, char *new_str)
{
	current->value = new_str;
	current->len = ft_strlen(new_str);
}
