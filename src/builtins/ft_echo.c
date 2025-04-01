#include "../../inc/minishell.h"

static int	is_valid_n_flag(const char *arg)
{
	int	i = 1;

	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(int argc, char **argv)
{
	int word_index = 1;
	int newline = 1; // first always print nl at end

	while (word_index < argc && is_valid_n_flag(argv[word_index]))
	{
		newline = 0;
		word_index++;
	}

// This prints the remaining arguments, separated by spaces.
// If there's another word after the current one, we add a space.
// echo hello world → prints "hello" then space, then "world".
	while (word_index < argc)
	{
		printf("%s", argv[word_index]);
		if (word_index + 1 < argc)
			printf(" ");
		word_index++;
	}

	if (newline)
		printf("\n");

	return (0);
}
