#include "minishell.h"

void	init_lexer(t_input *new_input, char *input_str)
{
    new_input->full_str = input_str;
    new_input->index = 0;
    new_input->len = ft_strlen(input_str);
    new_input->tokens = NULL;
}

static t_token *init_token(t_input *input, int len, int type)
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

static int	is_word(t_input *input, int word_len)
{
	if (input->full_str[input->index + word_len] &&
                   !ft_isspace(input->full_str[input->index + word_len]) &&
                   input->full_str[input->index + word_len] != '|' &&
                   input->full_str[input->index + word_len] != '<' &&
                   input->full_str[input->index + word_len] != '>')
		return (1);
	else
		return (0);
}

void extract_token(t_input *input, int start, int word_len)
{
    while (input->index < input->len)
    {
        while (input->full_str[input->index] == ' ')
            input->index++;
        if (input->full_str[input->index] == '\0')
            break;
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
        {
			start = input->index;
			word_len = input->index - start;
			while (is_word(input, word_len))
                word_len++;
            add_token(&input->tokens, init_token(input, word_len, WORD));
        }
    }
}
