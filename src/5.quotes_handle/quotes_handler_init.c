#include "../inc/minishell.h"

void	init_vars(t_minishell *mshell, t_vars *vars, t_token *current)
{
	init_quotes(&vars->quotes);
	vars->input_str = current->value;
	vars->new_str = ft_arena_strdup(mshell->arena, "");
	if (!vars->new_str)
		exit_cleanup_error(mshell, "malloc");
	vars->is_bare_exp = 1;
}
