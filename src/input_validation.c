#include "../inc/minishell.h"

int	quote_validation(char *input, t_quotes type, int *balanced)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (type == NONE)
		{
			if (input[i] == '\'')
				i += quote_validation(&input[i + 1], SINGLE, balanced);
			if (input[i] == '"')
				i += quote_validation(&input[i + 1], DOUBLE, balanced);
		}
		else if (type == SINGLE || type == DOUBLE)
		{
			if (input[i] == '\'' && type == SINGLE)
				return (i + 1);
			else if (input[i] == '"' && type == DOUBLE)
				return (i + 1);
		}
		i++;
	}
	if (type == SINGLE || type == DOUBLE)
		*balanced = 0;
	return (i);
}


void input_validation(char *input)
{
	int balanced;

	balanced = 1;
	quote_validation(input, NONE, &balanced);
	// brackets_validation(input, NONE, &balanced);
	if (balanced == 0)
		exit_error(BALANCE);
}
