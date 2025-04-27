/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:57:43 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/27 13:39:51 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_minishell(t_minishell *mshell, char **envp, t_ast **ast, char **av)
{
	(void) av;
	if (copy_env(&mshell->envp, envp) != SUCCESS)
	{
		ft_dprintf(2, UNREACHABLE);
		return (FAIL);
	}
	increment_shlvl(mshell->envp);
	mshell->exitcode = 0;
	mshell->in_child = 0;
	mshell->input_str = NULL;
	mshell->path = NULL;
	mshell->arena = NULL;
	mshell->rl_count = 0;
	mshell->rl_count_heredoc = 0;
	mshell->origin_stdin = -1;
	mshell->origin_stdout = -1;
	mshell->origin_stdin = -1; //dup(STDIN_FILENO);
	if (mshell->origin_stdin == -1)
		exit_cleanup_error(mshell, "dup");
	mshell->origin_stdout = dup(STDOUT_FILENO);
	if (mshell->origin_stdin == -1)
		exit_cleanup_error(mshell, "dup");
	if (mshell->origin_stdin < 0 || mshell->origin_stdout < 0)
		return (FAIL);
	*ast = NULL;
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
