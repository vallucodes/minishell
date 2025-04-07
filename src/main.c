#include "../inc/minishell.h"

int main(int ac, char **av, char **envp)
{
	char		*input_str;
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
		init_arena(&mshell.arena);
		input_str = readline(PROMPT);
		if (!input_str)
			break ;
		//guard for empty str "" OR "     "
		if (input_str[0] == '\0' || ft_is_all_whitespace(input_str)) // maybe include this in input validation, this seem like patch. Also this thing should be added to history
		{
			free(input_str);
			continue;
		}
		add_history(input_str);
		if (!input_validation(input_str))
		{
			init_lexer(&input, input_str);
			extract_token(&mshell, &input);
			if (tokens_validation(input.tokens) == SUCCESS)
			{
				retokenize_words(input.tokens);
				handle_heredoc(&mshell.arena, mshell.envp->envp, input.tokens);
				// print_tokens(input.tokens);
				expand_remove_quotes(mshell.envp->envp, input.tokens); //double quote or single quote expasion
				print_tokens(input.tokens);
				ast = build_ast_binary_tree(&mshell.arena, input.tokens);
				execute_builtins(&mshell, ast);
				free(input_str); // dont free this before the whole program ends!
			}
		}
		arena_destroy(&mshell.arena);
	}
	//free_env(&mshell.env); // must free environment here after loop end
	return (0);
}

// "l"s -la<file1>fi"le"1.1| "c"a't' -e >fi""l'e2' <<file3 | grep fi"l"en'am'e >>file4 | du -s > file5
