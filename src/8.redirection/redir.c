/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiennguy <hiennguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:32:40 by hiennguy          #+#    #+#             */
/*   Updated: 2025/04/26 21:37:56 by hiennguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	redirect_input(t_ast *ast);
static int	redirect_output(t_ast *ast);
static int	redirect_append(t_ast *ast);

int	handle_redirection(t_ast *ast)
{
	while (ast)
	{
		if (ast->type == REDIR_IN)
		{
			if (redirect_input(ast) == FAIL)
				return (FAIL);
		}
		else if (ast->type == REDIR_OUT)
		{
			if (redirect_output(ast) == FAIL)
				return (FAIL);
		}
		else if (ast->type == REDIR_APPEND)
		{
			if (redirect_append(ast) == FAIL)
				return (FAIL);
		}
		ast = ast->next_left;
	}
	return (SUCCESS);
}

static int	redirect_input(t_ast *ast)
{
	int	fd_in;

	fd_in = -1;
	if (open_redir_file(ast->file, O_RDONLY, &fd_in, ast) == FAIL)
		return (FAIL);
	if (safe_dup2(fd_in, STDIN_FILENO) == FAIL)
	{
		close(fd_in);
		return (FAIL);
	}
	close(fd_in);
	return (SUCCESS);
}

static int	redirect_output(t_ast *ast)
{
	int	fd_out;

	fd_out = -1;
	if (open_redir_file(ast->file, O_WRONLY | O_CREAT | O_TRUNC, &fd_out,
			ast) == FAIL)
		return (FAIL);
	if (safe_dup2(fd_out, STDOUT_FILENO) == FAIL)
	{
		close(fd_out);
		return (FAIL);
	}
	close(fd_out);
	return (SUCCESS);
}

static int	redirect_append(t_ast *ast)
{
	int	fd_out;

	fd_out = -1;
	if (open_redir_file(ast->file, O_WRONLY | O_CREAT | O_APPEND, &fd_out,
			ast) == FAIL)
		return (FAIL);
	if (safe_dup2(fd_out, STDOUT_FILENO) == FAIL)
	{
		close(fd_out);
		return (FAIL);
	}
	close(fd_out);
	return (SUCCESS);
}
