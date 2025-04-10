#include "minishell.h"

t_token	*skip_until_pipe_or_end(t_token *current)
{
	while (current != NULL && current->type != PIPE)
		current = current->next;
	return (current);
}
