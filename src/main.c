#include "../inc/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_input		input;
	t_ast		*ast;
	t_minishell	mshell;
	struct sigaction sa;

	(void) av;

	if (ac != 1)
		exit_error(NULL, AC);
	init_minishell(&sa, &mshell, envp, &ast);
	while (1)
	{
		signal_action_main();
		mshell.input_str = readline(PROMPT);
		signal_action_ignore();
		mshell.rl_count += 1;
		if (!mshell.input_str)
			exit_and_cleanup(&mshell);
		if (mshell.input_str[0] == '\0' && (free(mshell.input_str), 1))
			continue ;
		add_history(mshell.input_str);
		if (input_validation(mshell.input_str) && (free(mshell.input_str), 1))
			continue ;
		init_arena(&mshell);
		if (tokenizer(&mshell, &input) == FAIL)
			continue ;
		if (handle_heredoc(&mshell, input.tokens) == FAIL)
			continue ;
		expand_remove_quotes(&mshell, input.tokens);
		// print_tokens(input.tokens);
		build_ast_binary_tree(&mshell, input.tokens, &ast);
		mshell.command_count = 0;
		// print_whole_tree(ast);
		execute_ast(&mshell, ast);

        // Add this debug line:
        //ft_dprintf(2, "Debug: Main loop continued. Child exit code was: %d\n", mshell.exitcode);

		delete_tmp_files(&mshell);
		free(mshell.input_str);
		arena_delete(&mshell.arena);
	}
	delete_minishell(&mshell);
	//free_env(&mshell.env); // must free environment here after loop end
	return (0);
}

// ls -la<file1>fi"le"1.1| "c"a't' -e >fi""'le2' <'fi'le3 | cmd1 fi"l"en'am'e >>file4 | du -s > $HOME'/path'

// valgrind --leak-check=full --show-reachable=yes --track-fds=yes --error-limit=no --suppressions=./minimal.supp ./minishell
