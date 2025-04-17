#include "../inc/minishell.h"

t_ast	*init_node(t_minishell *mshell, char **cmd, char *file, t_token_type type)
{
	t_ast	*new_node;

	new_node = arena_alloc(mshell->arena, sizeof(t_ast), alignof(t_ast));
	if (!new_node)
		exit_cleanup_error(mshell, "malloc");
	new_node->type = type;
	new_node->cmd = cmd;
	new_node->file = file;
	new_node->next_left = NULL;
	new_node->next_right = NULL;
	return (new_node);
}

void	add_node(t_ast **ast, t_ast *new_node, t_order order)
{
	t_ast *temp;

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

t_ast	*build_ast_binary_tree(t_minishell *mshell, t_token *tokens)
{
	t_ast	*ast;
	size_t	amount_of_pipes;
	size_t	i;

	ast = NULL;
	i = 0;
	amount_of_pipes = get_amount_of_pipes(tokens);
	while (i < amount_of_pipes)
	{
		add_node(&ast, init_node(mshell, NULL, NULL, PIPE), FIRST);
		build_branch(mshell, &ast, tokens, NON_LAST_BRANCH);
		tokens = skip_to_next_pipe(tokens);
		i++;
	}
	build_branch(mshell, &ast, tokens, LAST_BRANCH);
	return (ast);
}
