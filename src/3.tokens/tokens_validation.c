#include "minishell.h"

static int	validate_tokens_looping(t_token *current)
{
	while (current != NULL)
	{
		if (current->type == PIPE || is_any_redirect(current))
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
		if (is_any_redirect(current) && !(current->next->type == WORD))
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
