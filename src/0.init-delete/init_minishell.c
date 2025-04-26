/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:57:43 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/26 16:30:13 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_minishell(t_minishell *mshell, char **envp, t_ast **ast, char **av)
{
	(void) av;
	if (copy_env(&mshell->envp, envp) != 0)
	{
		ft_dprintf(2, UNREACHABLE);
		return (FAIL);
	}
	increment_shlvl(mshell->envp);
	mshell->exitcode = 0;
	mshell->in_child = 0;
	mshell->path = NULL;
	mshell->arena = NULL;
	mshell->rl_count = 0;
	mshell->rl_count_heredoc = 0;
	mshell->origin_stdin = dup(STDIN_FILENO);
	mshell->origin_stdout = dup(STDOUT_FILENO);
	if (mshell->origin_stdin < 0 || mshell->origin_stdout < 0)
		return (FAIL);
	*ast = NULL;
	set_exitcode_signal(mshell);
	return (0);
}

void	init_quotes(t_quotes_helper *quotes)
{
	quotes->in_double = 0;
	quotes->in_single = 0;
	quotes->in_quotes = 0;
	quotes->previous_in_quotes = 0;
}
