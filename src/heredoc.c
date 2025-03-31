#include "../inc/minishell.h"

static int	is_valid_char(char c)
{
	return(ft_isalnum(c) || c == '_');
}

static size_t	expand_content(char **env, char *str, int fd)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = 1;
	while (str[len] && is_valid_char(str[len]))
		len++;
	i = 0;
	while(env[i])
	{
		if (ft_strncmp(&env[i][0], &str[1], len - 1) == 0)
		{
			j = 0;
			while (env[i][j])
			{
				while (env[i][j++] != '=')
				j++;
				while (env[i][j])
					write(fd, &env[i][j++], 1);
			}
		}
		i++;
	}
	return (len);
}

static void	save_to_file(char **env, char *input, int fd, t_expand expand)
{
	size_t	i;

	i = 0;
	if (expand == DONT_EXPAND)
	{
		while (input[i])
			write(fd, &input[i++], 1);
		write(fd, "\n", 1);
	}
	else
	{
		while (input[i])
		{
			if (input[i] == '$' && !ft_isspace(input[i + 1]))
				i += expand_content(env, &input[i], fd);
			else
				write(fd, &input[i++], 1);
		}
		write(fd, "\n", 1);
	}
}

static void	read_line(char **env, char *eof, t_expand expand)
{
	char	*input;
	int		fd;

	fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// if (!fd)
		// exit_error(FILE_ALREADY_EXISTS);
	input = readline(">");
	while (ft_strncmp(eof, input, ft_strlen(eof)) || (ft_strlen(input) != ft_strlen(eof)))
	{
		save_to_file(env, input, fd, expand);
		free(input);
		input = NULL;
		input = readline(">");
	}
	free(input);
	input = NULL;
	// save to file
}

void	handle_heredoc(char **env, t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current)
	{
		if (current->type == HERE_STRING)
		{
			read_line(env, current->value, EXPAND);
			// replace token
		}
		current = current->next;
	}
}
