#include "../inc/minishell.h"

int	is_any_word(t_token_type type)
{
	return ((type == COMMAND) || (type == ARG) || (type == FILE_TOKEN));
}

void	replace_content_of_token(t_token *current, char *new_str)
{
	current->value = new_str;
	current->len = ft_strlen(new_str);
}

static size_t	expand_content(char **env, char *str, char **new_str)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = 1;
	while (str[len] && is_valid_char_expansion(str[len]))
		len++;
	i = 0;
	while(env[i])
	{
		if (ft_strncmp(&env[i][0], &str[1], len - 1) == 0)
		{
			j = 0;
			while (env[i][j])
			{
				while (env[i][j++] != '=')
				j++;
				while (env[i][j++])
					append_char(env[i], new_str, j);
			}
		}
		i++;
	}
	return (len);
}

static void	loop_through_word(char **env, t_token *current)
{
	t_quotes_helper	quotes;
	char			*new_str;
	char			*input_str;
	size_t			i;

	i = 0;
	input_str = current->value;
	init_quotes(&quotes);
	new_str = ft_strdup("");
	while (input_str[i])
	{
		quotes.previous_in_quotes = quotes.in_quotes;
		quotes.in_quotes = inquotes(input_str[i], &quotes);
		if (!quotes.in_single && input_str[i] == '$' && is_valid_char_expansion(input_str[i + 1]))
			i += expand_content(env, &input_str[i], &new_str); //under work
		if (quotes.previous_in_quotes != quotes.in_quotes)
		{
			i++;
			continue ;
		}
		append_char(input_str, &new_str, i);
		i++;
	}
	replace_content_of_token(current, new_str);
}

void	expand_remove_quotes(char **env, t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current)
	{
		if (is_any_word(current->type))
			loop_through_word(env, current);
		current = current->next;
	}
}
