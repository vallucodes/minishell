#include "../inc/minishell.h"

int	count_amount_cmd(t_token *tokens)
{
	size_t	amount;

	amount = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == COMMAND)
			amount++;
		if (tokens->type == ARG)
			amount++;
		tokens = tokens->next;
	}
	return (amount);
}

size_t	get_amount_of_pipes(t_token *tokens)
{
	t_token	*tmp;
	size_t	amount;

	tmp = tokens;
	amount = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			amount++;
		tmp = tmp->next;
	}
	return (amount);
}
