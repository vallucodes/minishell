#include "../inc/minishell.h"

bool	is_pid_expansion(t_quotes_helper quotes, char *input_str)
{
	size_t	i;

	i = 0;
	return ((!quotes.in_single && input_str[i] == '$'
			&& input_str[i + 1] == '$'));
}

bool	is_exitcode_expansion(t_quotes_helper quotes, char *input_str)
{
	size_t	i;

	i = 0;
	return ((!quotes.in_single && input_str[i] == '$'
			&& input_str[i + 1] == '?'));
}

void	update_vars_quote(t_vars *vars, size_t *i)
{
	vars->is_bare_exp = 0;
	(*i)++;
}

void	update_vars_append(t_minishell *mshell, t_vars *vars, size_t *i)
{
	vars->is_bare_exp = 0;
	append_char(mshell, vars->input_str, &vars->new_str, *i);
	(*i)++;
}
