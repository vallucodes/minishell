#include "../inc/minishell.h"

int main(int ac, char **av, char **envp)
{

	t_input		input;
	t_ast		*ast;
	t_minishell	mshell;

	(void) av;

	if (ac != 1)
		return (FAIL);
		// exit_error(AC ERROR)
	if (init_minishell(&mshell, envp))
		return (FAIL);
		// exit_error(init_issue)
	while (1)
	{
		mshell.input_str = readline(PROMPT);
		if (!mshell.input_str)
		{
			continue;
			//exit_error(readline);
		}
			if (mshell.input_str[0] == '\0' && (free(mshell.input_str), 1))
			continue ;
		add_history(mshell.input_str);
		if (input_validation(mshell.input_str) && (free(mshell.input_str), 1))
			continue ;
		init_arena(&mshell.arena);
		if (tokenizer(&mshell, &input, mshell.input_str) == FAIL)
		{
			free(mshell.input_str);
			arena_destroy(&mshell.arena);
			continue ;
		}
		handle_heredoc(&mshell.arena, mshell.envp->envp, input.tokens);
		expand_remove_quotes(mshell.envp->envp, input.tokens);
		print_tokens(input.tokens);
		ast = build_ast_binary_tree(&mshell.arena, input.tokens); //change to send the adress of ast
		mshell.command_count = 0;
		print_whole_tree(ast);

		execute_ast(&mshell, ast);
		//free(mshell.input_str); have delete minishell
		arena_destroy(&mshell.arena);
	}
	delete_minishell(&mshell);
	//free_env(&mshell.env); // must free environment here after loop end
	return (0);
}

// ls -la<file1>fi"le"1.1| "c"a't' -e >fi""'le2' <<'fi'le3 | grep fi"l"en'am'e >>file4 | du -s > $HOME'/path'
