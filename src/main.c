#include "../inc/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_input		input;
	t_ast		*ast;
	t_minishell	mshell;
	struct sigaction sa;

	(void) av;

	if (ac != 1)
		exit_error(AC);
	init_minishell(&sa, &mshell, envp);
	while (1)
	{
		signal_action_main(mshell.sa);
		mshell.input_str = readline(PROMPT);
		signal_action_ignore(mshell.sa);
		if (!mshell.input_str)
			exit_and_cleanup(&mshell);
		if (mshell.input_str[0] == '\0' && (free(mshell.input_str), 1))
			continue ;
		add_history(mshell.input_str);
		if (input_validation(mshell.input_str) && (free(mshell.input_str), 1))
			continue ;
		init_arena(&mshell);
		if (tokenizer(&mshell, &input, mshell.input_str) == FAIL)
		{
			free(mshell.input_str);
			arena_destroy(&mshell.arena);
			continue ;
		}
		if (handle_heredoc(&mshell, input.tokens))
		{
			free(mshell.input_str);
			continue ;
		}
		signal_action_main(mshell.sa);
		expand_remove_quotes(&mshell, input.tokens);
		// print_tokens(input.tokens);
		ast = build_ast_binary_tree(&mshell.arena, input.tokens); //change to send the adress of ast
		mshell.command_count = 0;
		// print_whole_tree(ast);

		execute_ast(&mshell, ast);
		delete_tmp_files(&mshell.arena);
		//free(mshell.input_str); have delete minishell
		arena_destroy(&mshell.arena);
	}
	delete_minishell(&mshell);
	//free_env(&mshell.env); // must free environment here after loop end
	return (0);
}

// ls -la<file1>fi"le"1.1| "c"a't' -e >fi""'le2' <<'fi'le3 | cmd1 fi"l"en'am'e >>file4 | du -s > $HOME'/path'
