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
				|| ft_strcmp(ast->cmd[0], "env") == 0
				|| ft_strcmp(ast->cmd[0], "exit") == 0)
		)
			return (1);
		ast = ast->next_left;
	}
	return (0);
}

static char **remove_redir_args(char **cmd)
{
	int i;
	int j;

	i = 0;
	j = 0;
	char **cleaned = malloc(sizeof(char *) * ((count_argv(cmd)) + 1));
	if (!cleaned)
		return NULL;
	while (cmd[i])
	{
		if (ft_strlen(cmd[i]) == 1 && ft_isdigit(cmd[i][0]))
		{
			i++;
			continue;
		}
		if (ft_is_numeric(cmd[i]) && ft_strlen(cmd[i]) < 4)
		{
			i++;
			continue;
		}
		cleaned[j++] = ft_strdup(cmd[i++]);
	}
	cleaned[j] = NULL;
	return cleaned;
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
	char **clean_cmd;

	cmd_node = get_cmd_node(ast);
	if (!cmd_node || !cmd_node->cmd || !cmd_node->cmd[0])
		return FAIL;

	clean_cmd = remove_redir_args(cmd_node->cmd);
	if (!clean_cmd || !clean_cmd[0])
	{
		ft_free_2d(clean_cmd);
		return FAIL;
	}
	argc = count_argv(clean_cmd);
	mshell->exitcode = return_builtin(mshell, argc, clean_cmd);
	ft_free_2d(clean_cmd);
	return (mshell->exitcode);
}
