#include "../../inc/minishell.h"

static int	is_valid_n_flag(const char *arg);

int	ft_echo(int argv_count, char **argv)
{
	int word_index;
	int newline;

	word_index = 1;
	newline = 1; // first always print nl at end
	while (word_index < argv_count && is_valid_n_flag(argv[word_index]))
	{
		newline = 0;
		word_index++;
	}
	// This prints the remaining arguments, separated by spaces.
	// If there's another word after the current one, we add a space.
	// echo hello world → prints "hello" then space, then "world".
	while (word_index < argv_count)
	{
		printf("%s", argv[word_index]);
		if (word_index + 1 < argv_count)
			printf(" ");
		word_index++;
	}

	if (newline)
		printf("\n");

	return (0);
}

static int	is_valid_n_flag(const char *arg)
{
	int	i;

	i = 1;
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
