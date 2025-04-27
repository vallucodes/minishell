/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:45:51 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/27 15:35:00 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
