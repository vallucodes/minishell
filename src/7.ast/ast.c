/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:46:35 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 16:46:36 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	build_ast_binary_tree(t_minishell *mshell, t_token *tokens, t_ast **ast)
{
	size_t		amount_of_pipes;
	size_t		i;

	*ast = NULL;
	if (!tokens)
		return ;
	i = 0;
	amount_of_pipes = get_amount_of_pipes(tokens);
	while (i < amount_of_pipes)
	{
		add_node(ast, init_node(mshell, NULL, NULL, PIPE), FIRST);
		build_branch(mshell, ast, tokens, NON_LAST_BRANCH);
		tokens = skip_to_next_pipe(tokens);
		i++;
	}
	build_branch(mshell, ast, tokens, LAST_BRANCH);
}
