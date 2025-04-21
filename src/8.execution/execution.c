#include "../../inc/minishell.h"

int	execute_builtin_alone(t_minishell *mshell, t_ast *ast);
int	execute_in_sub_process(t_minishell *mshell, t_ast *ast);

void execute_ast_v1(t_minishell *mshell, t_ast *ast)
{
	if (ast->type != PIPE && is_builtin(ast))
		mshell->exitcode = execute_builtin_alone(mshell, ast);
	else
		mshell->exitcode = execute_in_sub_process(mshell, ast);
}

int execute_builtin_alone(t_minishell *mshell, t_ast *ast)
{
	if (handle_redirection(ast) == FAIL)
	{
		mshell->exitcode = 1;
		safe_dup2(mshell->origin_stdin, STDIN_FILENO);
		safe_dup2(mshell->origin_stdout, STDOUT_FILENO);
		return (FAIL);
	}
	mshell->exitcode = execute_builtin(mshell, ast);
	if (dup2(mshell->origin_stdin, STDIN_FILENO) < 0 || dup2(mshell->origin_stdout, STDOUT_FILENO) < 0)
		return (FAIL);
	return (mshell->exitcode);
}

int execute_in_sub_process(t_minishell *mshell, t_ast *ast)
{
	t_exec	exec;
	t_ast	*current;

	exec.prev_fd = -1;
	exec.command_count = 0;
	current = ast;
	while (current)
	{
		exec.has_pipe = (current->next_right != NULL);
		if (setup_pipe(&exec) == FAIL)
			return FAIL;
		if (setup_fork(&exec) == FAIL)
			return FAIL;
		if (exec.pid == 0)
		{
			mshell->in_child = 1;
			handle_child_process(mshell, current, &exec);
		}
		else
			setup_parent_pipe_fds(mshell, &exec);
		current = current->next_right;
	}
	mshell->exitcode = wait_for_children(&exec);
	return (mshell->exitcode);
}











