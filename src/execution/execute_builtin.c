#include "../../inc/minishell.h"
#include "../../inc/builtin.h"


int execute_builtin(t_minishell *mshell, t_ast *ast)
{
	if (!mshell || !ast || !ast->cmd || !ast->cmd[0])
	{
		ft_dprintf(2, "minishell: builtin execution error\n");
		mshell->exitcode = FAIL;
		return (mshell->exitcode);
	}
	if (ft_strcmp(ast->cmd[0], "env") == 0)
	{
		mshell->exitcode = ft_env(&mshell->envp, ast->cmd);
		return (mshell->exitcode);
	}
	if (ft_strcmp(ast->cmd[0], "pwd") == 0)
	{
		mshell->exitcode = ft_pwd();
		return (mshell->exitcode);
	}
	if (ft_strcmp(ast->cmd[0], "echo") == 0)
	{
		mshell->exitcode = ft_echo(count_cmds(ast->cmd), ast->cmd);
		return (mshell->exitcode);
	}
	if (ft_strcmp(ast->cmd[0], "exit") == 0)
	{
		ft_exit(ast->cmd, mshell);
		return (mshell->exitcode);
	}
	if (ft_strcmp(ast->cmd[0], "unset") == 0)
	{
		ft_unset(ast->cmd, mshell->envp);
		return (mshell->exitcode);
	}
	if (ft_strcmp(ast->cmd[0], "export") == 0)
	{
		ft_export(ast->cmd, mshell->envp);
		return (mshell->exitcode);
	}
	return (FAIL); //no built-in matched
}


