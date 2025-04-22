#include "../inc/minishell.h"

static char	*add_command(t_token *tokens)
{
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == COMMAND)
			return (tokens->value);
		tokens = tokens->next;
	}
	return (NULL);
}

static char	**find_cmd_and_compose(t_minishell *mshell, t_token *tokens)
{
	char	*arg;
	char	**cmd;
	int		i;

	i = 0;
	cmd = arena_alloc(mshell->arena, \
		(count_amount_cmd(tokens) + 1) * sizeof(char *), alignof(char *));
	if (!cmd)
		exit_cleanup_error(mshell, "malloc");
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

static void	build_branch_add_redirects(t_minishell *mshell, \
			t_ast **ast, t_token *tokens, t_branch branch)
{
	t_token	*tmp;

	tmp = tokens;
	if (branch == LAST_BRANCH)
	{
		while (tmp && tmp->type != PIPE)
		{
			if (is_any_redirect(tmp))
			{
				add_node(ast, init_node(mshell, NULL, \
						tmp->next->value, tmp->type), FIRST);
				tmp = tmp->next;
				break ;
			}
			tmp = tmp->next;
		}
	}
	while (tmp && tmp->type != PIPE)
	{
		if (is_any_redirect(tmp))
			add_node(ast, init_node(mshell, NULL, \
					tmp->next->value, tmp->type), NON_FIRST);
		tmp = tmp->next;
	}
}

static void	build_branch_add_command(t_minishell *mshell, \
			t_ast **ast, t_token *tokens, t_branch branch)
{
	t_token	*tmp;
	char	**cmd;

	tmp = tokens;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == COMMAND)
		{
			cmd = find_cmd_and_compose(mshell, tmp);
			if (branch == LAST_BRANCH && last_is_pipe(ast))
				add_node(ast, init_node(mshell, cmd, \
						NULL, tmp->type), FIRST);
			else
				add_node(ast, init_node(mshell, cmd, \
						NULL, tmp->type), NON_FIRST);
		}
		tmp = tmp->next;
	}
}

void	build_branch(t_minishell *mshell, \
		t_ast **ast, t_token *tokens, t_branch branch)
{
	build_branch_add_redirects(mshell, ast, tokens, branch);
	build_branch_add_command(mshell, ast, tokens, branch);
}
