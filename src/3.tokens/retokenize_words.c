#include "minishell.h"

static void	set_commands(t_token *tokens)
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

static void	set_redirects(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current != NULL && current->next != NULL)
	{
		if (is_any_redirect(current) && current->type != HERE_DOCUMENT)
			current->next->type = FILE_TOKEN;
		current = current->next;
	}
}

static void	set_heredocs(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current != NULL && current->next != NULL)
	{
		if (current->type == HERE_DOCUMENT)
			current->next->type = HERE_TOKEN;
		current = current->next;
	}
}

static void	set_arguments(t_token *tokens)
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
