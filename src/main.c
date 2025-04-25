#include "../inc/minishell.h"

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
		sig_action_main(&mshell);
		// if (isatty(fileno(stdin)))
		mshell.input_str = readline(PROMPT);
		// else
		// {
		// 	char *line;
		// 	line = get_next_line(fileno(stdin));
		// 	mshell.input_str = ft_strtrim(line, "\n");
		// 	free(line);
		// }
		sig_action_ignore(&mshell);
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
		expand_remove_quotes(&mshell, &input);
		// print_tokens(input.tokens);
		build_ast_binary_tree(&mshell, input.tokens, &ast);
		// print_whole_tree(ast);
		execute_ast_v1(&mshell, ast);
        //ft_dprintf(2, "Debug: Main loop continued. Child exit code was: %d\n", mshell.exitcode);
		delete_tmp_files(&mshell);
		free(mshell.input_str);
		arena_delete(&mshell.arena);
	}
	delete_minishell(&mshell);
	return (0);
}

// ls -la<file1>fi"le"1.1| "c"a't' -e >fi""'le2' <'fi'le3 | cmd1 fi"l"en'am'e >>file4 | du -s > $HOME'/path'

// valgrind --leak-check=full --show-reachable=yes --track-fds=yes --error-limit=no --suppressions=./minimal.supp ./minishell

// $H echo a


// vlopatin@c1r6p13:~/c/Main_studies/minishell (copy)$ export x="a s"
// vlopatin@c1r6p13:~/c/Main_studies/minishell (copy)$ >$x
// bash: $x: ambiguous redirect,
// issue here is that we should print original token "$x".
