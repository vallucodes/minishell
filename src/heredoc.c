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

void	next_temp_file(char *file, int nb)
{
	char	*char_nb;
	int		i;
	int		j;

	file[0] = 't';
	file[1] = 'm';
	file[2] = 'p';
	char_nb = ft_itoa(nb);
	// if (!char_nb)
		// exit_error(MALLOC);
	i = 3;
	j = 0;
	while (char_nb[j])
	{
		file[i] = char_nb[j];
		i++;
		j++;
	}
	file[i] = '\0';
	free(char_nb);
}


int	create_tmp_file()
{
	int		fd;
	char	file[256];
	int		index;

	index = 1;
	while (1)
	{
		ft_bzero(file, 256);
		next_temp_file(file, index);
		if (access (file, F_OK) != 0)
			break ;
		index++;
		// if (index > 1000)
			// exit_error(TOO MANY TEMP FILES)
	}
	fd = open(file, O_WRONLY | O_CREAT | O_EXCL, 0644);
	// if (fd < 0)
		// exit_error(TMP_FILE_CREATION_FAILED);
	return (fd);
}

static void	read_line(char **env, char *eof, t_expand expand)
{
	char	*input;
	int		fd;

	fd = create_tmp_file();
	input = readline(">");
	while (ft_strncmp(eof, input, ft_strlen(eof)) || (ft_strlen(input) != ft_strlen(eof)))
	{
		save_to_file(env, input, fd, expand);
		free(input);
		input = NULL;
		input = readline("> ");
	}
	free(input);
	input = NULL;
}

void	replace_token(t_token *current)
{
	current->value++;
	current->len = 1;
	current->type = REDIRECT_IN;
	current->next->type = FILE_TOKEN;
	// current->next->value = tmp;
}

void	handle_heredoc(char **env, t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current)
	{
		if (current->type == HERE_STRING)
		{
			read_line(env, current->next->value, EXPAND);
			replace_token(current);
		}
		current = current->next;
	}
}
