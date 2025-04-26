/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:46:24 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 16:56:27 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*extract_pid(t_minishell *mshell, char *buffer)
{
	size_t	i;
	size_t	len;
	char	*str_pid;

	len = 0;
	while (buffer[len] && !ft_isspace(buffer[len]))
		len++;
	str_pid = arena_alloc(mshell->arena, len + 1, alignof(char));
	if (!str_pid)
		exit_cleanup_error(mshell, "malloc");
	i = 0;
	while (i < len)
	{
		str_pid[i] = buffer[i];
		i++;
	}
	str_pid[i] = '\0';
	return (str_pid);
}

size_t	expand_pid(t_minishell *mshell, int fd, char **new_str)
{
	char	*str_pid;
	char	buf[256];
	int		fd_get_pid;
	int		bytes_read;

	fd_get_pid = open("/proc/self/stat", O_RDONLY);
	if (fd_get_pid == -1)
	{
		write_or_add_to_str(mshell, fd, new_str, "$\0");
		return (1);
	}
	bytes_read = read(fd_get_pid, buf, sizeof(buf) - 1);
	if (bytes_read <= 0)
	{
		close(fd_get_pid);
		write_or_add_to_str(mshell, fd, new_str, "$\0");
		return (1);
	}
	buf[bytes_read] = '\0';
	str_pid = extract_pid(mshell, buf);
	write_or_add_to_str(mshell, fd, new_str, str_pid);
	close(fd_get_pid);
	return (2);
}

size_t	expand_content(t_minishell *mshell, char *str, int fd, char **new_str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	**env;

	env = mshell->envp->envp;
	len = get_len_explandeble(str);
	i = -1;
	while (env[++i])
	{
		if (expandable_exists(len, env, i, str))
		{
			j = skip_to_start_of_expandable(env[i]);
			while (env[i][j])
			{
				if (fd)
					write(fd, &env[i][j], 1);
				else if (new_str)
					append_char(mshell, env[i], new_str, j);
				j++;
			}
		}
	}
	return (len);
}

size_t	expand_exitcode_value(t_minishell *mshell, int fd, char **new_str)
{
	char	*str_nb;
	size_t	i;
	int		exitcode;

	exitcode = mshell->exitcode;
	str_nb = ft_itoa(exitcode);
	if (!str_nb)
		exit_cleanup_error(mshell, "malloc");
	i = 0;
	while (str_nb[i])
	{
		if (fd)
			write(fd, &str_nb[i], 1);
		else if (new_str)
			append_char(mshell, str_nb, new_str, i);
		i++;
	}
	free(str_nb);
	return (2);
}

int	handle_expandables(t_minishell *mshell,
			t_vars *vars, size_t *i, t_token *current)
{
	if (is_valid_expandable(vars->quotes, &vars->input_str[*i])
		&& !is_ambiguous_redirect
		(mshell, vars->quotes, current, &vars->input_str[*i]))
	{
		*i += expand_content(mshell, &vars->input_str[*i], 0, &vars->new_str);
		return (SUCCESS);
	}
	else if (is_pid_expansion(vars->quotes, &vars->input_str[*i]))
	{
		vars->is_bare_exp = 0;
		*i += expand_pid(mshell, 0, &vars->new_str);
		return (SUCCESS);
	}
	else if (is_exitcode_expansion(vars->quotes, &vars->input_str[*i]))
	{
		vars->is_bare_exp = 0;
		*i += expand_exitcode_value(mshell, 0, &vars->new_str);
		return (SUCCESS);
	}
	return (FAIL);
}
