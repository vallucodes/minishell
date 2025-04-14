#include "minishell.h"



// typedef struct s_minishell
// {
// 	t_arena		*arena;
// 	t_env		*envp; // env struct
// 	int			exitcode; //exitcode assignment after exe
// 	char		*path;
// 	int			command_count;
// 	pid_t		*pids;
// 	//later add execution, exit code when we are there
// }				t_minishell ;

void	arena_destroy(t_arena **a)
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

	arena_destroy(&mshell->arena);
}
