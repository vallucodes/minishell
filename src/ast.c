#include "../inc/minishell.h"

char	*add_command(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == COMMAND)
			return (tokens->value);
		tokens = tokens->next;
	}
	return (NULL);
}

char	**find_cmd_and_compose(t_token *tokens)
{
	char	*arg;
	char	**cmd;
	int		i;

	i = 0;
	cmd = (char **)malloc((count_amount_cmd(tokens) + 1) * sizeof(char *));
	// if (!cmd)
	// 	exit_error(MALLOC); to-do
	cmd[i] = add_command(tokens);
	tokens = tokens->next;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == ARG)
			cmd[++i] = tokens->value;
		tokens = tokens->next;
	}
	cmd[++i] = NULL;
	return (cmd);
}

t_token	*skip_to_next_pipe(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
		tokens = tokens->next;
	if (tokens == NULL)
		return (tokens);
	else
		return (tokens->next);
}

t_ast *init_node(char **cmd, char *file, t_token_type type, int id)
{
	t_ast	*new_node;

	new_node = (t_ast *)malloc(sizeof(t_ast));
	// if (!new_node)
	// 	exit_error(MALLOC);
	new_node->type = type;
	new_node->cmd = cmd;
	new_node->file = file;
	new_node->id = id;
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

void build_branch(t_ast **ast, t_token *tokens)
{
	t_token	*tmp;
	char	**cmd;

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if ((tmp->type == REDIRECT_IN) || (tmp->type == REDIRECT_OUT) || (tmp->type == REDIRECT_APPEND))
			add_node(ast, init_node(NULL, tmp->next->value, tmp->type, 0), NON_FIRST);
		tmp = tmp->next;
	}
	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == COMMAND)
		{
			cmd = find_cmd_and_compose(tmp);
			add_node(ast, init_node(cmd, NULL, tmp->type, 0), NON_FIRST);
		}
		tmp = tmp->next;
	}
}

int	last_is_pipe(t_ast **ast)
{
	t_ast *temp;

	temp = *ast;
	while (temp->next_right)
		temp = temp->next_right;
	if (temp->type == PIPE)
		return (1);
	return (0);

}

void	branch_add_redirects(t_ast **ast, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if ((tmp->type == REDIRECT_IN) || (tmp->type == REDIRECT_OUT) || (tmp->type == REDIRECT_APPEND))
		{
			add_node(ast, init_node(NULL, tmp->next->value, tmp->type, 0), FIRST);
			tmp = tmp->next;
			break ;
		}
		tmp = tmp->next;
	}
	while (tmp && tmp->type != PIPE)
	{
		if ((tmp->type == REDIRECT_IN) || (tmp->type == REDIRECT_OUT) || (tmp->type == REDIRECT_APPEND))
			add_node(ast, init_node(NULL, tmp->next->value, tmp->type, 0), NON_FIRST);
		tmp = tmp->next;
	}
}

void	build_last_branch(t_ast **ast, t_token *tokens)
{
	t_token	*tmp;
	char	**cmd;

	branch_add_redirects(ast, tokens);

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == COMMAND)
		{
			cmd = find_cmd_and_compose(tmp);
			if (last_is_pipe(ast))
				add_node(ast, init_node(cmd, NULL, tmp->type, 0), FIRST);
			else
				add_node(ast, init_node(cmd, NULL, tmp->type, 0), NON_FIRST);
		}
		tmp = tmp->next;
	}
}

t_ast	*build_ast_binary_tree(t_token *tokens)
{
	t_ast	*ast;
	size_t	amount_of_pipes;
	size_t	i;

	ast = NULL;
	i = 0;
	amount_of_pipes = get_amount_of_pipes(tokens);
	while (i < amount_of_pipes)
	{
		add_node(&ast, init_node(NULL, NULL, PIPE, i), FIRST);
		build_branch(&ast, tokens);
		tokens = skip_to_next_pipe(tokens);
		i++;
	}
	build_last_branch(&ast, tokens);
	print_whole_tree(ast);
	return (ast);
}
//ls -la < file1 > file1.1| cat -e > file2 | grep filename > file3 | du -s > file4
