/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:40:37 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 17:40:38 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	g_signal = 0;

int main(int ac, char **av, char **envp)
{
	t_input		input;
	t_ast		*ast;
	t_minishell	mshell;

	(void) av;

	if (ac != 1)
		exit_error(NULL, AC);
	init_minishell(&mshell, envp, &ast);
	while (1)
	{
		//
		sig_action_main(&mshell);
		mshell.input_str = readline(PROMPT);
		sig_action_ignore(&mshell);
		mshell.rl_count += 1;
		if (!mshell.input_str)
			exit_and_cleanup(&mshell);
		if (mshell.input_str[0] == '\0' && (free(mshell.input_str), 1))
			continue ;
		add_history(mshell.input_str);
		//
		if (input_validation(&mshell) && (free(mshell.input_str), 1))
			continue ;
		init_arena(&mshell);
		if (tokenizer(&mshell, &input) == FAIL)
			continue ;
		if (handle_heredoc(&mshell, input.tokens) == FAIL)
			continue ;
		expand_remove_quotes(&mshell, &input);
		//print_tokens(input.tokens);
		build_ast_binary_tree(&mshell, input.tokens, &ast);
		// print_whole_tree(ast);

		//
		execute_ast(&mshell, ast);

		delete_tmp_files(&mshell);
		free(mshell.input_str);
		arena_delete(&mshell.arena);
	}
	delete_minishell(&mshell);
	return (0);
}



// ls -la<file1>fi"le"1.1| "c"a't' -e >fi""'le2' <'fi'le3 | cmd1 fi"l"en'am'e >>file4 | du -s > $HOME'/path'
// ls -la<file1>fi"le"1.1| "c"a't' -e >fi""'le2' <<'fi'le3 | grep fi"l"en'am'e >>file4 | du -s > $HOME'/path'
// ls -la<file1>fi"le"1.1| "c"a't' -e >fi""'le2' <<'fi'le3 | grep fi"l"en'am'e >>file4 | du -s > "$HO'ME"'/path'

//valgrind --leak-check=full --show-reachable=yes --track-fds=yes --error-limit=no --suppressions=./minimal.supp ./minishell


// OPT+CMD+(number)
// handle this limiting the input length in input validation

