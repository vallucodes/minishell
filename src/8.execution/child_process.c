#include "../../inc/minishell.h"

static int exec_external_command(t_minishell *mshell, t_ast *ast)
{
	char *full_cmd_path;
	t_ast *cmd_node;

	cmd_node = get_cmd_node(ast);
	if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd[0])
		return FAIL;
	full_cmd_path = get_command_path(mshell, cmd_node);
	//printf("COMMAND OR ARGS COUNT: %d\n", count_argv(cmd_node->cmd));
	sig_action_default(mshell);
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

void	handle_child_process(t_minishell *mshell, t_ast *ast, t_exec *exec)
{
	close_origin_fds(mshell);
	setup_child_pipe_fds(mshell, exec);
	if (handle_redirection(ast) == FAIL)
		exit(1);
	if (is_builtin(ast))
	{
		mshell->exitcode = execute_builtin(mshell, ast);
		delete_minishell(mshell);
		exit(mshell->exitcode);
	}
	else
		exec_external_command(mshell, ast);
	exit(SUCCESS);
}

