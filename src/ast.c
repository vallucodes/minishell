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
	// new_node->previous = NULL;
	return (new_node);
}

void	add_node(t_ast **ast, t_ast *new_node)
{
	t_ast *temp;

	if (!new_node || !ast)
		return ;
	if (!*ast)
		*ast = new_node;
	else if (new_node->type == PIPE)
	{
		temp = *ast;
		while (temp->next_right)
			temp = temp->next_right;
		temp->next_right = new_node;
	}
	else
	{
		temp = *ast;
		while (temp->next_right)
			temp = temp->next_right;
		while (temp->next_left)
			temp = temp->next_left;
		temp->next_left = new_node;
	}
}

void	print_left_side(t_ast *ast)
{
	t_ast	*tmp;

	tmp = ast;
	while (tmp)
	{
		printf("Type: %15s id:%i ", get_token_type_name(tmp->type), tmp->id);
		if (tmp->cmd == NULL)
			printf("Cmd: NULL ");
		else
			printf("Cmd: %s ", tmp->cmd[0]);
		if (tmp->file == NULL)
			printf("file: NULL \n");
		else
			printf("file: %s\n", tmp->file);
		tmp = tmp->next_left;
	}
}

void	print_whole_tree(t_ast *ast)
{
	while (ast)
	{
		printf("Type: %15s id:%i ", get_token_type_name(ast->type), ast->id);
		if (ast->cmd == NULL)
			printf("Cmd: NULL ");
		else
			printf("Cmd: %s ", ast->cmd[0]);
		if (ast->file == NULL)
			printf("file: NULL \n");
		else
			printf("file: %s\n", ast->file);
		if (ast->next_left == NULL)
			ast = ast->next_right;
		else
		{
			print_left_side(ast);
			ast = ast->next_right;
		}
	}
}

void build_branch(t_ast **ast, t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if ((tmp->type == REDIRECT_IN) || (tmp->type == REDIRECT_OUT) || (tmp->type == REDIRECT_APPEND))
			add_node(ast, init_node(NULL, tmp->next->value, tmp->type, 0));
		tmp = tmp->next;
	}
}

t_ast	*build_ast_binary_tree(t_token *tokens)
{
	t_ast	*ast;

	ast = NULL;
	int i = 1;
	while (tokens)
	{
		add_node(&ast, init_node(NULL, NULL, PIPE, i));
		build_branch(&ast, tokens);
		tokens = skip_to_next_pipe(tokens);
		// printf("--------------PIPE---------------------\n\n");
		// free(cmd);
		// cmd = NULL;
	}
	print_whole_tree(ast);
	// ast = return_to_head(ast);
	return (ast);
}
//ls -la < file1 > file1.1| cat -e > file2 | grep filename > file3 | du -s > file4
