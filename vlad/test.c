#include <strings.h>
#include <stdio.h>
#include "../inc/minishell.h"

size_t	expand_content(char *str, int fd)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = 0;
	while (str[len] && !ft_isspace(str[len]))
		len++;
	i = 0;
	while(envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (ft_strncmp(&envp[i][0], &str[1], len - 1) == 0)
			{
				while (envp[i][j] != "\"")
					j++;
				while (envp[i][j] != "\"")
					write(fd, envp[j++], 1);
			}
		}
		i++;
	}
	return (len);
}

void	save_to_file(char *input, int fd, t_expand expand)
{
	size_t	i;

	i = 0;
	if (expand == DONT_EXPAND)
	{
		while (input[i])
			write(fd, input[i++], 1);
		write(fd, "\n", 1);
	}
	else
	{
		while (input[i])
		{
			if (input[i] == '$' && !ft_isspace(input[i + 1]))
				i += expand_content(&input[i], fd);
			write(fd, input[i++], 1);
		}
		write(fd, "\n", 1);
	}
}

void	read_line(char *eof, t_expand expand)
{
	char	*input;
	int		fd;

	fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	input = readline(">");
	save_to_file(input, fd, expand);
	free(input);
	input = NULL;
	while (ft_strncmp(eof, input, ft_strlen(eof)) || (ft_strlen(input) != ft_strlen(eof)))
	{
		input = readline(">");
		save_to_file(input, fd, expand);
		free(input);
		input = NULL;
	}
	// save to file
}

int main(int ac, char **av)
{
	if (ac == 2)
		read_line(av[1], EXPAND);
	return 0;
}
