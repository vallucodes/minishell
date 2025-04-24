#include "../inc/minishell.h"

void static	init_pipe(t_ast *new_node)
{
	new_node->cmd = NULL;
	new_node->file = NULL;
	new_node->type = PIPE;
	new_node->ambiguous = 0;
}

void static	init_redir(t_ast *new_node, t_token *tokens)
{
	new_node->cmd = NULL;
	new_node->file = tokens->next->value;
	new_node->type = tokens->type;
	new_node->ambiguous = tokens->next->ambiguous;
}

void static	init_cmd(t_ast *new_node, t_token *tokens, char **cmd)
{
	new_node->cmd = cmd;
	new_node->file = NULL;
	new_node->type = tokens->type;
	new_node->ambiguous = 0;
}

t_ast	*init_node(t_minishell *mshell, \
		char **cmd, t_token *tokens, t_token_type type)
{
	t_ast	*new_node;

	new_node = arena_alloc(mshell->arena, sizeof(t_ast), alignof(t_ast));
	if (!new_node)
		exit_cleanup_error(mshell, "malloc");
	if (type == PIPE)
		init_pipe(new_node);
	else if (is_any_redirect(tokens))
		init_redir(new_node, tokens);
	else if (tokens->type == COMMAND)
		init_cmd(new_node, tokens, cmd);
	new_node->next_left = NULL;
	new_node->next_right = NULL;
	return (new_node);
}

void	add_node(t_ast **ast, t_ast *new_node, t_order order)
{
	t_ast	*temp;

	if (!new_node || !ast)
		return ;
	if (!*ast)
	{
		*ast = new_node;
		return ;
	}
	if (order == FIRST)
	{
		temp = *ast;
		while (temp->next_right)
			temp = temp->next_right;
		temp->next_right = new_node;
	}
	else if (order == NON_FIRST)
	{
		temp = *ast;
		while (temp->next_right)
			temp = temp->next_right;
		while (temp->next_left)
			temp = temp->next_left;
		temp->next_left = new_node;
	}
}
