#include "../inc/minishell.h"

int	is_eof(char *eof, char *input)
{
	return(!(ft_strncmp(eof, input, ft_strlen(eof)) ||
		(ft_strlen(input) != ft_strlen(eof))));
}

int	is_valid_char_expansion(char c)
{
	return(ft_isalnum(c) || c == '_');
}

void	save_to_file(t_minishell *mshell, char *input, int fd, t_expand expand)
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
			if (input[i] == '$' && is_valid_char_expansion(input[i + 1]))
				i += expand_content(mshell, &input[i], fd, NULL);
			else if (input[i] == '$' && input[i + 1] == '$')
				i += expand_pid(mshell, fd, NULL);
			else if (input[i] == '$' && input[i + 1] == '?')
				i += expand_exitcode_value(mshell, fd, NULL);
			else
				write(fd, &input[i++], 1);
		}
		write(fd, "\n", 1);
	}
}

void	next_tmp_file(char *file, int nb)
{
	char	*char_nb;
	int		i;
	int		j;

	file[0] = 't';
	file[1] = 'm';
	file[2] = 'p';
	char_nb = ft_itoa(nb);
	// if (!char_nb)
		// exit_cleanup_error(mshell, "malloc");
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

char	*create_tmp_file(t_minishell *mshell, int *fd)
{
	char	*tmp_file;
	int		index;

	tmp_file = arena_alloc(mshell->arena, NAME_MAX + 1, alignof(char));
	// if (!tmp_file)
		// exit_cleanup_error(mshell, "malloc");
	index = 1;
	while (1)
	{
		ft_bzero(tmp_file, NAME_MAX + 1);
		next_tmp_file(tmp_file, index);
		if (access (tmp_file, F_OK) != 0)
			break ;
		index++;
		// if (index > 1000)
			// exit_error(TOO MANY TEMP FILES)
	}
	*fd = open(tmp_file, O_WRONLY | O_CREAT | O_EXCL, 0644);
	// if (fd < 0)
		// exit_cleanup_error(mshell, "file");
	return (tmp_file);
}
