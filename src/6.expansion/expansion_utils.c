/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlopatin <vlopatin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:46:22 by vlopatin          #+#    #+#             */
/*   Updated: 2025/04/26 16:56:43 by vlopatin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

size_t	skip_to_start_of_expandable(char *env_row)
{
	size_t	i;

	i = 0;
	while (env_row[i] && env_row[i] != '=')
		i++;
	i++;
	return (i);
}

size_t	get_len_explandeble(char *str)
{
	size_t	len;

	len = 1;
	while (str[len] && is_valid_char_expansion(str[len]))
		len++;
	return (len);
}

void	write_or_add_to_str(t_minishell *mshell,
		int fd, char **new_str, char *str_pid)
{
	size_t	i;

	i = 0;
	while (str_pid[i])
	{
		if (fd)
			write(fd, &str_pid[i], 1);
		else if (new_str)
			append_char(mshell, str_pid, new_str, i);
		i++;
	}
}
