/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:54:50 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/27 18:30:44 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int		wait_input(t_minishell *mshell);
static int		validate_input(t_minishell *mshell);
static int		parse_input(t_minishell *mshell, t_input *input, t_ast **ast);
static void		cleanup_after_execution(t_minishell *mshell);

void	run_minishell(t_minishell *mshell, t_input *input, t_ast **ast)
{
	while (1)
	{
		if (wait_input(mshell) == FAIL)
			continue ;
		if (validate_input(mshell) == FAIL)
			continue ;
		if (parse_input(mshell, input, ast) == FAIL)
			continue ;
		execute_ast(mshell, *ast);
		cleanup_after_execution(mshell);
	}
}

static int	wait_input(t_minishell *mshell)
{
	sig_action_main(mshell);
	mshell->input_str = readline(PROMPT);
	sig_action_ignore(mshell);
	mshell->rl_count++;
	if (!mshell->input_str)
		exit_and_cleanup(mshell);
	if (mshell->input_str[0] == '\0')
	{
		free(mshell->input_str);
		return (FAIL);
	}
	add_history(mshell->input_str);
	return (SUCCESS);
}

static int	validate_input(t_minishell *mshell)
{
	if (input_validation(mshell) == FAIL)
	{
		free(mshell->input_str);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	parse_input(t_minishell *mshell, t_input *input, t_ast **ast)
{
	init_arena(mshell);
	if (tokenizer(mshell, input) == FAIL)
		return (FAIL);
	if (handle_heredoc(mshell, input->tokens) == FAIL)
		return (FAIL);
	expand_remove_quotes(mshell, input);
	build_ast_binary_tree(mshell, input->tokens, ast);
	return (SUCCESS);
}

static void	cleanup_after_execution(t_minishell *mshell)
{
	delete_tmp_files(mshell);
	free(mshell->input_str);
	arena_delete(&mshell->arena);
}
