#include "minishell.h"

int	tokenizer(t_minishell *mshell, t_input *input, char *input_str)
{
	init_lexer(input, input_str);
	create_tokens(mshell, input);
	if (tokens_validation(input->tokens) == FAIL)
		return (FAIL);
	retokenize_words(input->tokens);
	return (SUCCESS);
}
// ls -la<file1>fi"le"1.1| "c"a't' -e >fi""'le2' <<'fi'le3 | grep fi"l"en'am'e >>file4 | du -s > $HOME'/path'
// ls -la<file1>fi"le"1.1| "c"a't' -e >fi""'le2' <<'fi'le3 | grep fi"l"en'am'e >>file4 | du -s > "$HO'ME"'/path'
