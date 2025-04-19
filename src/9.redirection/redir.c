#include "../../inc/minishell.h"

static int	redirect_input(t_ast *ast)
{
	int	fd_in;

	fd_in = -1;
	if (open_redir_file(ast->file, O_RDONLY, &fd_in) == FAIL)
		return (FAIL);

	if (fd_in != -1)
	{
		if (safe_dup2(fd_in, STDIN_FILENO) == FAIL)
			return (FAIL);
		close(fd_in);
	}
	return (SUCCESS);
}

static int	redirect_output(t_ast *ast)
{
	int	fd_out;

	fd_out = -1;
	if (open_redir_file(ast->file, O_WRONLY | O_CREAT | O_TRUNC, &fd_out) == FAIL)
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
	if (open_redir_file(ast->file, O_WRONLY | O_CREAT | O_APPEND, &fd_out) == FAIL)
		return (FAIL);

	if (safe_dup2(fd_out, STDOUT_FILENO) == FAIL)
	{
		close(fd_out);
		return (FAIL);
	}
	close(fd_out);
	return (SUCCESS);
}

int	handle_redirection(t_ast *ast)
{
	while (ast)
	{
		if (ast->type == REDIRECT_IN)
		{
			if (redirect_input(ast) == FAIL)
				return (FAIL);
		}
		else if (ast->type == REDIRECT_OUT)
		{
			if (redirect_output(ast) == FAIL)
				return (FAIL);
		}
		else if (ast->type == REDIRECT_APPEND)
		{
			if (redirect_append(ast) == FAIL)
				return (FAIL);
		}
		ast = ast->next_left;
	}
	return (SUCCESS);
}

