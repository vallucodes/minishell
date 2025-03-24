#include "minishell.h"

static int	is_separator(char c)
{
	return(c == '<' || c == '>' || c == '|' || c == '<' || ft_isspace(c) || c == '\0');
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	is_operator(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '<');
}

void	init_lexer(t_input *new_input, char *input_str)
{
	new_input->full_str = input_str;
	new_input->index = 0;
	new_input->len = ft_strlen(input_str);
	new_input->tokens = NULL;
}

static t_token *init_token(t_input *input, int len, t_token_type type)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = &input->full_str[input->index];
	new_token->len = len;
	new_token->type = type;
	new_token->next = NULL;
	input->index += len;
	return (new_token);
}

static t_token *init_token_word(int len, t_token_type type, char *word)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = &word[0];
	new_token->len = len;
	new_token->type = type;
	new_token->next = NULL;
	// input->index += len;
	return (new_token);
}

static void add_token(t_token **head, t_token *new)
{
	t_token *last;
	if (new == NULL)
		return;
	if (*head == NULL)
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

static int	is_word(t_input *input, int i)
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

int	inquotes(char c, int *in_double, int *in_single)
{
	if (c == '\'' && !*in_double)
		*in_single = !*in_single;
	else if (c == '\"' && !*in_single)
		*in_double = !*in_double;
	return (*in_double || *in_single);
}

static char	*word2(t_input *input)
{
	int		in_double;
	int		in_single;
	int		in_quotes;
	char	*new;
	char	*str;

	str = input->full_str;
	in_double = 0;
	in_single = 0;
	in_quotes = 0;
	new = ft_strdup("");
	while (input->full_str[input->index] && (!is_separator(input->full_str[input->index] || in_quotes)))
	{
		in_quotes = inquotes(input->full_str[input->index], &in_double, &in_single);
		if (!in_quotes && is_quote(str[input->index]))
		{}
		else
		{
			char additive[2] = {str[input->index], '\0'};
			new = ft_strjoin(new, additive);
		}
		input->index++;
	}
	return (new);
}

static void	word(t_input *input, int word_len)
{
	char *new;
	new = word2(input);
	input->index++;
	add_token(&input->tokens, init_token_word(word_len, WORD_DOUBLE, new));
	input->index++;
}

void extract_token(t_input *input)
{
	while (input->index < input->len)
	{
		while (input->full_str[input->index] == ' ')
			input->index++;
		if (input->full_str[input->index] == '\0')
			break ;
		if (ft_strncmp(&input->full_str[input->index], "<<", 2) == 0)
			add_token(&input->tokens, init_token(input, 2, HERE_STRING));
		else if (ft_strncmp(&input->full_str[input->index], ">>", 2) == 0)
			add_token(&input->tokens, init_token(input, 2, REDIRECT_APPEND));
		else if (input->full_str[input->index] == '|')
			add_token(&input->tokens, init_token(input, 1, PIPE));
		else if (input->full_str[input->index] == '<')
			add_token(&input->tokens, init_token(input, 1, REDIRECT_IN));
		else if (input->full_str[input->index] == '>')
			add_token(&input->tokens, init_token(input, 1, REDIRECT_OUT));
		else
			word(input, 0);
	}
}
