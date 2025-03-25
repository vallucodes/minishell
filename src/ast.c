#include "../inc/minishell.h"

t_token	*find_command(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == COMMAND)
			return (tokens);
		tokens = tokens->next;
	}
	return (NULL);
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

void	build_ast_binary_tree(t_token *tokens)
{
	t_ast	*ast;
	t_token	*cmd;
	t_token	*file;
	t_token	*here;

	while (tokens)
	{
		cmd = find_command(tokens);
		printf("cmd %s\n", cmd->value);
		file = find_file(tokens);
		printf("file %s\n", file->value);
		here = find_herestr(tokens);
		printf("here %s\n", here->value);
		// build_branch(cmd, file, here);
		printf("cmd %s, file %s, here %s\n", cmd->value, file->value, here->value);
		tokens = skip_to_next_pipe(tokens);
	}
}
