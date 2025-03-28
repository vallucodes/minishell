#include "../inc/minishell.h"

void	read_line(char *eof)
{
	char *input;

	input = NULL;
	while (!ft_strncmp(eof, input, ft_strlen(input) - 1))
		input = readline(PROMPT);
	// save to file
}

void	handle_heredoc(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current)
	{
		if (current->type == HERE_STRING)
		{
			read_line(current->value);
			// replace token
		}
		current = current->next;
	}
}
