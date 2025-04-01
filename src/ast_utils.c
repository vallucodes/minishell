#include "../inc/minishell.h"

t_token	*skip_to_next_pipe(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (tokens == NULL)
		return (tokens);
	else
		return (tokens->next);
}

int	last_is_pipe(t_ast **ast)
{
	t_ast *temp;

	if (!*ast)
		return (0);
	temp = *ast;
	while (temp->next_right)
		temp = temp->next_right;
	if (temp->type == PIPE)
		return (1);
	return (0);
}

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

int	is_any_redirect(t_token_type type)
{
	return ((type == REDIRECT_IN) || (type == REDIRECT_OUT) || (type == REDIRECT_APPEND));
}
