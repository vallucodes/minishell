#include "../inc/minishell.h"

void	print_helper(t_token *tokens, char *type)
{
	if (tokens)
		printf("%s: %s\n", type, tokens->value);
	else
		printf("%s: NULL\n", type);
}

void	print_cmd(char **cmd)
{
	int i;

	i = -1;
	printf("arg and cmds:\n");
	while (cmd[++i])
		printf("%s\n", cmd[i]);
	printf("\n");
}

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

int	count_amount(t_token *tokens)
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

char	**find_cmd_and_compose(t_token *tokens)
{
	char	*arg;
	char	**cmd;
	int		i;

	i = 0;
	cmd = (char**)malloc((count_amount(tokens) + 1) * sizeof(char *));
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

char	*find_file(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == FILE_TOKEN)
			return (tokens->value);
		tokens = tokens->next;
	}
	return (NULL);
}

char	*find_herestr(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == HERE_TOKEN)
			return (tokens->value);
		tokens = tokens->next;
	}
	return (NULL);
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

t_ast *init_node(char **cmd, char *file, char *here, t_token_type type)
{
	t_ast	*new_node;

	new_node = (t_ast *)malloc(sizeof(t_ast));
	// if (!new_node)
	// 	exit_error(MALLOC);
	new_node->type = type;
	new_node->cmd = cmd;
	new_node->file = file;
	new_node->next_left = NULL;
	new_node->next_right = NULL;
	new_node->next_right = NULL;
	return (new_node);
}

t_ast *build_branch(char **cmd, char *file, char *here, t_token_type type)
{
	t_ast *ast;
	if (type == PIPE)
		add_node(ast, init_node(NULL, NULL, NULL, PIPE));
	else if (type == (REDIRECT_APPEND || REDIRECT_IN || REDIRECT_OUT))
		add_node(ast, init_node(NULL, file, NULL, type));
	else if (type == (HERE_STRING))
		add_node(ast, init_node(NULL, NULL, here, HERE_STRING));
	else if (type == (COMMAND || ARG))
		add_node(ast, init_node(cmd, NULL, NULL, COMMAND));
}

void	build_ast_binary_tree(t_token *tokens, t_ast *ast)
{
	char	**cmd;
	char	*file;
	char	*here;

	while (tokens)
	{
		cmd = find_cmd_and_compose(tokens);
		// print_cmd(cmd);
		redir_left = find_redir_left(tokens);
		// print_helper(file, "file");
		redir_right = find_redir_right(tokens);
		// print_helper(here, "here");
		ast = build_branch(cmd, file, here, tokens->type);
		tokens = skip_to_next_pipe(tokens);
		// printf("--------------PIPE---------------------\n\n");
		free(cmd);
		cmd = NULL;
	}
}

//ls -la < file1 | cat -e > file2 | grep filename > file3 | du -s > file4
