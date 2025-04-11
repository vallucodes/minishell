#include "../inc/minishell.h"

int main(int ac, char **av, char **envp)
{
	char		*input_str;
	t_input		input;
	t_ast		*ast;
	t_minishell	mshell;
	struct sigaction sa;

	(void) av;

	if (ac != 1)
		return (FAIL);
		// exit_error(AC ERROR)
	if (init_minishell(&sa, &mshell, envp))
		return (FAIL);
		// exit_error(init_issue)
	while (1)
	{
		input_str = readline(PROMPT);
		ignore_signal_action(mshell.sa);
		// if (!input_str)
			// free(envp);
			// exit_error(readline);
		if (input_str[0] == '\0' && (free(input_str), 1))
			continue ;
		add_history(input_str);
		if (input_validation(input_str) && (free(input_str), 1))
			continue ;
		init_arena(&mshell.arena);
		if (tokenizer(&mshell, &input, input_str) == FAIL)
		{
			free(input_str);
			arena_destroy(&mshell.arena);
			continue ;
		}
		handle_heredoc(&mshell.arena, mshell, input.tokens);
		expand_remove_quotes(mshell.envp->envp, mshell.exitcode, input.tokens);
		print_tokens(input.tokens);
		ast = build_ast_binary_tree(&mshell.arena, input.tokens); //change to send the adress of ast
		print_whole_tree(ast);
		execute_builtins(&mshell, ast);
		mshell.exitcode = 66;
		free(input_str); // dont free this before the whole program ends!
		arena_destroy(&mshell.arena);
		restart_signal_action(mshell.sa);
	}
	//free_env(&mshell.env); // must free environment here after loop end
	return (0);
}

// ls -la<file1>fi"le"1.1| "c"a't' -e >fi""'le2' <<'fi'le3 | grep fi"l"en'am'e >>file4 | du -s > $HOME'/path'
