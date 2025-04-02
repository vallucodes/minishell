#include "../../inc/minishell.h"
#include "../../inc/builtin.h"

static int count_args(char **args)
{
	int count = 0;
	while (args && args[count])
		count++;
	return count;
}

int execute_builtins(t_minishell *mshell, t_ast *ast)
{
	if (!mshell || !ast || !ast->cmd || !ast->cmd[0])
	{
		ft_dprintf(2, "minishell: builtin execution error\n");
		mshell->exitcode = FAIL;
		return (mshell->exitcode);
	}
	if (ft_strcmp(ast->cmd[0], "env") == 0)
	{
		mshell->exitcode = ft_env(&mshell->envp, &ast->cmd[1]);
		return (mshell->exitcode);
	}
	if (ft_strcmp(ast->cmd[0], "pwd") == 0)
	{
		mshell->exitcode = ft_pwd();
		return (mshell->exitcode);
	}
	if (ft_strcmp(ast->cmd[0], "echo") == 0)
	{
		mshell->exitcode = ft_echo(count_args(ast->cmd), ast->cmd);
		return (mshell->exitcode);
	}
	if (ft_strcmp(ast->cmd[0], "exit") == 0)
	{
		ft_exit(ast->cmd, mshell);
		return (mshell->exitcode);
	}
	return (FAIL); //no built-in matched
}


