#include "../inc/minishell.h"

int main()
{
	char *input;

	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		printf("Input: %s\n", input);
		free(input);
	}
	return (0);
}
