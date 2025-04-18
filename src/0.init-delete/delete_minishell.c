#include "minishell.h"

void	arena_delete(t_arena **a)
{
	t_arenablock	*block;
	t_arenablock	*next;

	if (!a || !*a)
		return ;
	block = (*a)->first;
	while (block)
	{
		next = block->next;
		free(block);
		block = next;
	}
	free(*a);
	// printf("Arena destroyed\n");
	*a = NULL;
}

static void	delete_path(t_minishell *mshell)
{
	int	i;

	if (mshell->path == NULL)
		return ;
	i = 0;
	while (mshell->path[i])
	{
		free(mshell->path[i]);
		i++;
	}
	free(mshell->path);
	mshell->path = NULL;
}

void	delete_minishell(t_minishell *mshell)
{
	if (mshell == NULL)
		return ;
	delete_path(mshell);
	free_env(mshell->envp);
	free(mshell->envp);
	mshell->envp = NULL;
	free(mshell->input_str);
	arena_delete(&mshell->arena);
	rl_clear_history();
	if (mshell->origin_stdin >= 0)
		close(mshell->origin_stdin);
	if (mshell->origin_stdout >= 0)
		close(mshell->origin_stdout);
}

void	exit_and_cleanup(t_minishell *mshell)
{
	delete_minishell(mshell);
	rl_clear_history();
	ft_dprintf(1, "exit\n");
	exit(0);
}
