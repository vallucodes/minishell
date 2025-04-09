#include "minishell.h"

int	any_redirect(t_token *current)
{
	return(current->type == REDIRECT_IN ||
			current->type == REDIRECT_OUT ||
			current->type == REDIRECT_APPEND ||
			current->type == HERE_DOCUMENT);
}

static int	validate_tokens_looping(t_token *current)
{
	while (current != NULL)
	{
		if (current->type == PIPE || any_redirect(current))
		{
			if (current->next == NULL)
			{
				print_error(TOKEN_ERROR, NEWLINE_ERROR, 0);
				return (FAIL);
			}
			else if (current->next->type == PIPE)
			{
				print_error(TOKEN_ERROR, NULL, current->next->type);
				return (FAIL);
			}
		}
		if (any_redirect(current) && !(current->next->type == WORD))
		{
			print_error(TOKEN_ERROR, NULL, current->next->type);
			return (FAIL);
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	tokens_validation(t_token *tokens)
{
	t_token *current;

	current = tokens;
	if (current->type == PIPE)
	{
		print_error(TOKEN_ERROR, PIPE_ERROR, 0);
		return (FAIL);
	}
	if (validate_tokens_looping(current) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
