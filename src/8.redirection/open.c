/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:32:11 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/25 20:32:13 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_ambiguous_redir(const char *file, t_ast *ast);

int	open_redir_file(const char *file, int flags, int *fd, t_ast *ast)
{
	if (check_ambiguous_redir(file, ast) == FAIL)
		return (FAIL);
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
	*fd = open(file, flags, 0644);
	if (*fd < 0)
	{
		ft_dprintf(2, "Giraffeshell: %s: %s\n", file, strerror(errno), errno);
		return (FAIL);
	}
	return (SUCCESS);
}

static int	check_ambiguous_redir(const char *file, t_ast *ast)
{
	if (ast->ambiguous)
	{
		if (file)
			ft_dprintf(2, "Giraffeshell: %s: ambiguous redirect\n", file);
		else
			ft_dprintf(2, "Giraffeshell: : ambiguous redirect\n");
		return (FAIL);
	}
	return (SUCCESS);
}
