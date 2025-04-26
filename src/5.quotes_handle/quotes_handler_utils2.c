/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:46:12 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 20:35:14 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_pid_expansion(t_quotes_helper quotes, char *input_str)
{
	return ((!quotes.in_single && input_str[0] == '$'
			&& input_str[1] == '$'));
}

bool	is_exitcode_expansion(t_quotes_helper quotes, char *input_str)
{
	return ((!quotes.in_single && input_str[0] == '$'
			&& input_str[1] == '?'));
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

bool	process_expandable(size_t i, t_token *current, char	**env)
{
	size_t	j;

	j = skip_to_start_of_expandable(env[i]);
	if (env[i][j] == '\0')
		return (current->ambiguous = 1, 1);
	while (env[i][j])
	{
		if (current && ft_isspace(env[i][j]))
			return (current->ambiguous = 1, 1);
		j++;
	}
	return (0);
}
