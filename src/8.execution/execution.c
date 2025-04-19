#include "../../inc/minishell.h"
#include <sys/wait.h>
#include <sys/stat.h>

t_ast *get_cmd_node(t_ast *ast)
{
	while (ast)
	{
		if (ast->type == COMMAND)
			return (ast);
		ast = ast->next_left;
	}
	return (NULL);
}

static int exec_external_command(t_minishell *mshell, t_ast *ast)
{
	char *full_cmd_path;
	t_ast *cmd_node;

	cmd_node = get_cmd_node(ast);
	if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd[0])
		return FAIL;

	full_cmd_path = get_command_path(mshell, cmd_node);
	//printf("COMMAND OR ARGS COUNT: %d\n", count_argv(cmd_node->cmd));
	execve(full_cmd_path, cmd_node->cmd, mshell->envp->envp);
	ft_dprintf(2, "Giraffeshell: %s: %s\n", cmd_node->cmd[0], strerror(errno));
	mshell->exitcode = 1;
	if (errno == ENOENT)
		mshell->exitcode = 127;
	else if (errno == EACCES || errno == EISDIR || errno == ENOTDIR)
		mshell->exitcode = 126;

	free(full_cmd_path);
	delete_minishell(mshell);
	exit(mshell->exitcode);
}

static void	handle_child_process(t_minishell *mshell, t_ast *ast, t_exec *exec)
{
	close_origin_fds(mshell); // closes duped std fds in child
	setup_child_pipe_fds(mshell, exec);
	if (handle_redirection(ast) == FAIL)
		exit(1);

	if (is_builtin(ast))
		exit(execute_builtin(mshell, ast));
	else
		exec_external_command(mshell, ast);
	exit(127);
}

int execute_in_sub_process(t_minishell *mshell, t_ast *ast)
{
	t_exec	exec;
	t_ast	*current;
	int		exitcode = 0;

	exec.prev_fd = -1;
	exec.status = 0;
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
			handle_child_process(mshell, current, &exec);
		else
			setup_parent_pipe_fds(&exec);

		current = current->next_right;
	}
	exitcode = wait_for_children(&exec);
	return (exitcode);
}

void execute_ast_v1(t_minishell *mshell, t_ast *ast)
{
	if (ast->type != PIPE && is_builtin(ast))
		mshell->exitcode = execute_builtin_alone(mshell, ast);
	else
		mshell->exitcode = execute_in_sub_process(mshell, ast);
}

