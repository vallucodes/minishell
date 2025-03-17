#include "minishell.h"

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

static void	no_quotes(t_input *input)
{
	int word_len;

	word_len = 0;
	while (is_word(input, word_len))
		word_len++;
	add_token(&input->tokens, init_token(input, word_len, WORD_DOUBLE)); // maybe we will need this to be separate token like WORD, depending how this is handled later related to expansions and so on
}

static void	double_quotes(t_input *input)
{
	int word_len;

	word_len = 0;
	while (input->full_str[input->index + 1 + word_len] != '"')
		word_len++;
	input->index++;
	add_token(&input->tokens, init_token(input, word_len, WORD_DOUBLE));
	input->index++;
}

static void	single_quotes(t_input *input)
{
	int word_len;

	word_len = 0;
	while (input->full_str[input->index + 1 + word_len] != '\'')
		word_len++;
	input->index++;
	add_token(&input->tokens, init_token(input, word_len, WORD_SINGLE));
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
		else if (input->full_str[input->index] == '\'')
			single_quotes(input);
		else if (input->full_str[input->index] == '"')
			double_quotes(input);
		else
			no_quotes(input);
	}
}
