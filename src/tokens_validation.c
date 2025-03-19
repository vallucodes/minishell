#include "minishell.h"

int	validate_pipes_loop(t_token *current)
{
	while (current != NULL)
	{
		if (current->next != NULL)
		{
			if (current->type == PIPE && current->next->type == PIPE)
			{
				print_error(TOKEN_ERROR, PIPE_ERROR);
				return (FAIL);
			}
		}
		else
		{
			if (current->type == PIPE)
			{
				print_error(TOKEN_ERROR, NEWLINE_ERROR);
				return (FAIL);
			}
		}
		current = current->next;
	}
	return (SUCCESS);
}

static int	validate_pipes(t_token *tokens)
{
	t_token *current;

	current = tokens;
	if (current->type == PIPE)
	{
		print_error(TOKEN_ERROR, PIPE_ERROR);
		return (FAIL);
	}
	if (validate_pipes_loop(current) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

static int	validate_redirections(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current != NULL)
	{
		if ((current->type == REDIRECT_IN ||
			current->type == REDIRECT_OUT ||
			current->type == REDIRECT_APPEND ||
			current->type == HERE_STRING))
		{
			print_tokens(tokens);
			if (current->next == NULL)
				print_error(TOKEN_ERROR, NEWLINE_ERROR);
			else if (current->next->type == PIPE)
				print_error(TOKEN_ERROR, PIPE_ERROR);
			return (FAIL);
		}
		current = current->next;
	}
	return (SUCCESS);
}

int tokens_validation(t_token *tokens)
{
	// printf("return %i\n", validate_pipes(tokens));
	if (validate_pipes(tokens) == FAIL ||
		validate_redirections(tokens) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
