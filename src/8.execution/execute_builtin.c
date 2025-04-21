#include "../../inc/minishell.h"

int	is_builtin(t_ast *ast)
{
	while (ast)
	{
		if (
			ast->type == COMMAND
			&& (ft_strcmp(ast->cmd[0], "echo") == 0
				|| ft_strcmp(ast->cmd[0], "cd") == 0
				|| ft_strcmp(ast->cmd[0], "pwd") == 0
				|| ft_strcmp(ast->cmd[0], "export") == 0
				|| ft_strcmp(ast->cmd[0], "unset") == 0
				|| ft_strcmp(ast->cmd[0], "env") == 0	//printf("FINAL EXIT CODE IS %d\n", exitcode);
				|| ft_strcmp(ast->cmd[0], "exit") == 0)
		)
			return (1);
		ast = ast->next_left;
	}
	return (0);
}

static int return_builtin(t_minishell *mshell, int argc, char **argv)
{
	if (!argv || !argv[0])
		return (FAIL);

	if (ft_strcmp(argv[0], "env") == 0)
		return ft_env(&mshell->envp, argv);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		return ft_pwd();
	else if (ft_strcmp(argv[0], "echo") == 0)
		return ft_echo(argc, argv);
	else if (ft_strcmp(argv[0], "cd") == 0)
		return ft_cd(&mshell->envp, argc, argv);
	else if (ft_strcmp(argv[0], "exit") == 0)
	{
		ft_exit(argv, mshell);
		return mshell->exitcode;
	}
	else if (ft_strcmp(argv[0], "unset") == 0)
		return ft_unset(argv, mshell->envp);
	else if (ft_strcmp(argv[0], "export") == 0)
	{
		mshell->exitcode = ft_export(argv, mshell);
		return mshell->exitcode;
	}
	return FAIL;
}

int execute_builtin(t_minishell *mshell, t_ast *ast)
{
	int argc;
	t_ast *cmd_node;

	cmd_node = get_cmd_node(ast);
	if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd[0])
		return FAIL;
	argc = count_argv(cmd_node->cmd);
	mshell->exitcode = return_builtin(mshell, argc, cmd_node->cmd);
	return (mshell->exitcode);
}


