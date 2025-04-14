#include "minishell.h"

int	is_separator(char c)
{
	return(c == '<' || c == '>' || c == '|' || c == '<' || ft_isspace(c) || c == '\0');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '<');
}

int	is_valid_char(t_quotes_helper *quotes, t_input *input)
{
	return (input->full_str[input->index] &&
		((!is_separator(input->full_str[input->index]) || quotes->in_quotes)));
}

void	update_quote_state(char c, t_quotes_helper *quotes)
{
	quotes->previous_in_quotes = quotes->in_quotes;
	if (c == '\'' && !quotes->in_double)
		quotes->in_single = !quotes->in_single;
	else if (c == '\"' && !quotes->in_single)
		quotes->in_double = !quotes->in_double;
	quotes->in_quotes = (quotes->in_double || quotes->in_single);
}
