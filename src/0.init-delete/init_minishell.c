/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:57:43 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/27 15:41:39 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_mshell_vars(t_minishell *mshell, t_ast **ast)
{
	mshell->exitcode = 0;
	mshell->in_child = 0;
	mshell->input_str = NULL;
	mshell->path = NULL;
	mshell->arena = NULL;
	mshell->envp = NULL;
	mshell->rl_count = 0;
	mshell->rl_count_heredoc = 0;
	mshell->origin_stdin = -1;
	mshell->origin_stdout = -1;
	*ast = NULL;
}

int	init_minishell(t_minishell *mshell, char **envp, t_ast **ast, char **av)
{
	(void) av;
	init_mshell_vars(mshell, ast);
	if (copy_env(&mshell->envp, envp) != SUCCESS)
	{
		ft_dprintf(2, UNREACHABLE);
		return (FAIL);
	}
	increment_shlvl(mshell->envp);
	mshell->origin_stdin = dup(STDIN_FILENO);
	if (mshell->origin_stdin == -1)
		exit_cleanup_error(mshell, "dup");
	mshell->origin_stdout = dup(STDOUT_FILENO);
	if (mshell->origin_stdout == -1)
		exit_cleanup_error(mshell, "dup");
	set_exitcode_signal(mshell);
	return (SUCCESS);
}

void	init_quotes(t_quotes_helper *quotes)
{
	quotes->in_double = 0;
	quotes->in_single = 0;
	quotes->in_quotes = 0;
	quotes->previous_in_quotes = 0;
}
