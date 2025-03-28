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

int	is_word(t_input *input, int i)
{
	if (input->full_str[input->index + i] &&
		!ft_isspace(input->full_str[input->index + i]) &&
		input->full_str[input->index + i] != '|' &&
		input->full_str[input->index + i] != '<' &&
		input->full_str[input->index + i] != '>' &&
		input->full_str[input->index + i] != '\'' &&
		input->full_str[input->index + i] != '"')
		return (1);
	else
		return (0);
}

int	inquotes(char c, t_quotes_helper *quotes)
{
	if (c == '\'' && !quotes->in_double)
		quotes->in_single = !quotes->in_single;
	else if (c == '\"' && !quotes->in_single)
		quotes->in_double = !quotes->in_double;
	return (quotes->in_double || quotes->in_single);
}
