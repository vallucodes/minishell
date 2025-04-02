#include <stdio.h>

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
	int newline = 1; // always print nl at end

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

int main()
{
	// Test the is_valid_n_flag function
	printf("Testing is_valid_n_flag:\n");
	printf("-nn-nnn: %d\n", is_valid_n_flag("-nn-nnn")); //  should be 0
	printf("-nnn:    %d\n", is_valid_n_flag("-nnn"));    // should be 1
	printf("-n:      %d\n", is_valid_n_flag("-n"));      // should be 1
	printf("--nnn:   %d\n", is_valid_n_flag("--nnn"));   // should be 0
	printf("-:       %d\n", is_valid_n_flag("-"));       // should be 0
	printf("no dash: %d\n", is_valid_n_flag("nnn"));     // should be 0

	// Simulate echo call
	printf("\nTesting ft_echo:\n");
	char *args1[] = {"echo", "-n", "-nn", "hello", "world"};
	ft_echo(5, args1);  // Output: hello world (no newline)

	printf("\n");

	char *args2[] = {"echo", "hello", "-nnn", "--nnn"};
	ft_echo(4, args2);  // Output: hello -nnn --nnn (with newline)

	printf("\n");

	return 0;
}
