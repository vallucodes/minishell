#include "minishell.h"

// Before calling this function, validation of tokens order and all error situations in input MUST be handled
// because there are no guards for changing types of nodes

static t_token	*skip_until_pipe_or_end(t_token *current)
{
	while (current != NULL && current->type != PIPE)
		current = current->next;
	return (current);
}

void	set_commands(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == WORD)
		{
			current->type = COMMAND;
			current = skip_until_pipe_or_end(current);
		}
		else
			current = current->next;
	}
}

void	set_redirects(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current != NULL && current->next != NULL)
	{
		if (any_redirect(current) && current->type != HERE_STRING)
			current->next->type = FILE_TOKEN;
		current = current->next;
	}
}

void	set_heredocs(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current != NULL && current->next != NULL)
	{
		if (current->type == HERE_STRING)
			current->next->type = HERE_TOKEN;
		current = current->next;
	}
}

void	set_arguments(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current != NULL)
	{
		if (current->type == WORD)
			current->type = ARG;
		current = current->next;
	}
}

void	retokenize_words(t_token *tokens)
{
	set_heredocs(tokens);
	set_redirects(tokens);
	set_commands(tokens);
	set_arguments(tokens);
	return ;
}
