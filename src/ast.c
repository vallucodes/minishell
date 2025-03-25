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

t_token	*find_file(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == FILE_TOKEN)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
}

t_token	*find_herestr(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == HERE_TOKEN)
			return (tokens);
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

void	build_ast_binary_tree(t_token *tokens, t_ast *ast)
{
	char	**cmd;
	t_token	*file;
	t_token	*here;

	while (tokens)
	{
		cmd = find_cmd_and_compose(tokens);
		print_cmd(cmd);
		file = find_file(tokens);
		print_helper(file, "file");
		here = find_herestr(tokens);
		print_helper(here, "here");
		// build_branch(cmd, file, here);
		tokens = skip_to_next_pipe(tokens);
		printf("--------------PIPE---------------------\n\n");
		free(cmd);
		cmd = NULL;
	}
}

//ls -la < file1 | cat -e > file2 | grep filename > file3 | du -s > file4
