#include "../inc/minishell.h"

int	is_valid_char_expansion(char c)
{
	return(ft_isalnum(c) || c == '_');
}

static int	skip_to_start_of_expandable(char *env_row)
{
	int	i;

	i = 0;
	while (env_row[i] && env_row[i] != '=')
		i++;
	i++;
	return (i);
}

size_t	expand_content(char **env, char *str, int fd, char **new_str)
{
	size_t	i;
	size_t	j;
	size_t	len;

	len = 1;
	while (str[len] && is_valid_char_expansion(str[len]))
		len++;
	i = -1;
	while(env[++i])
	{
		if (expandable_exists(len, env, i, str))
		{
			j = skip_to_start_of_expandable(env[i]);
			while (env[i][j])
			{
				if (fd)
					write(fd, &env[i][j], 1);
				else if (new_str)
					append_char(env[i], new_str, j);
				j++;
			}
		}
	}
	return (len);
}

char	*extract_pid(char *buffer)
{
	size_t	i;
	size_t	len;
	char	*pid_str;

	len = 0;
	while (buffer[len] && !ft_isspace(buffer[len]))
		len++;
	pid_str = malloc(len + 1);
	// if (!pid_str)
	// 	exit_error(MALLOC);
	i = 0;
	while (i < len)
	{
		pid_str[i] = buffer[i];
		i++;
	}
	pid_str[i] = '\0';
	return (pid_str);
}

void	write_or_add_to_str(int fd, char **new_str, char *str_pid)
{
	size_t	i;

	i = 0;
	while (str_pid[i])
	{
		if (fd)
			write(fd, &str_pid[i], 1);
		else if (new_str)
			append_char(str_pid, new_str, i);
		i++;
	}
}

size_t	expand_pid(int fd, char **new_str)
{
	char	*str_pid;
	char	buf[256];
	int		fd_get_pid;
	size_t	bytes_read;

	fd_get_pid = open("/proc/self/stat", O_RDONLY);
	if (fd_get_pid == -1)
	{
		write_or_add_to_str(fd, new_str, "$\0");
		return (1);
	}
	bytes_read = read(fd_get_pid, buf, sizeof(buf) - 1);
	if (bytes_read <= 0)
	{
		write_or_add_to_str(fd, new_str, "$\0");
		return (1);
	}
	close(fd_get_pid);
	buf[bytes_read] = '\0';
	str_pid = extract_pid(buf);
	write_or_add_to_str(fd, new_str, str_pid);
	free(str_pid);
	return (2);
}

void	save_to_file(char **env, char *input, int fd, t_expand expand)
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
				i += expand_content(env, &input[i], fd, NULL);
			else if (input[i] == '$' && input[i + 1] == '$')
				i += expand_pid(fd, NULL);
			else
				write(fd, &input[i++], 1);
		}
		write(fd, "\n", 1);
	}
}

static void	next_temp_file(char *file, int nb)
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

char	*create_tmp_file(t_arena **arena, int *fd)
{
	char	*file;
	int		index;

	// file = malloc(256);
	file = arena_alloc(*arena, 10, alignof(char));
	// if (!file)
		// exit_error(MALLOC);
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
	*fd = open(file, O_WRONLY | O_CREAT | O_EXCL, 0644);
	// if (fd < 0)
	{
		// free(file);
		// exit_error(TMP_FILE_CREATION_FAILED);
	}
	return (file);
}
