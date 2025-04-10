#include "../inc/minishell.h"

static int	skip_to_start_of_expandable(char *env_row)
{
	int	i;

	i = 0;
	while (env_row[i] && env_row[i] != '=')
		i++;
	i++;
	return (i);
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
