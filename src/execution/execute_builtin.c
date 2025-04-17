#include "../../inc/minishell.h"

int execute_builtin(t_minishell *mshell, char **cmd_args)
{
	//ft_dprintf(2, "%p\t%p\n", mshell, ast);
	//ft_dprintf(2, "%p\n", ast->cmd);
	if (!mshell || !cmd_args || !cmd_args[0])
	{
		ft_dprintf(2, "Giraffeshell: builtin execution error\n");
		mshell->exitcode = FAIL;
		return (mshell->exitcode);
	}
	if (ft_strcmp(cmd_args[0], "env") == 0)
	{
		mshell->exitcode = ft_env(&mshell->envp, cmd_args);
		return (mshell->exitcode);
	}
	if (ft_strcmp(cmd_args[0], "pwd") == 0)
	{
		mshell->exitcode = ft_pwd();
		return (mshell->exitcode);
	}
	if (ft_strcmp(cmd_args[0], "echo") == 0)
	{
		mshell->exitcode = ft_echo(count_argv(cmd_args), cmd_args);
		return (mshell->exitcode);
	}
	if (ft_strcmp(cmd_args[0], "cd") == 0)
	{
		mshell->exitcode = ft_cd(&mshell->envp, count_argv(cmd_args), cmd_args);
		return (mshell->exitcode);
	}
	if (ft_strcmp(cmd_args[0], "exit") == 0)
	{
		ft_exit(cmd_args, mshell);
		return (mshell->exitcode);
	}
	if (ft_strcmp(cmd_args[0], "unset") == 0)
	{
		ft_unset(cmd_args, mshell->envp);
		return (mshell->exitcode);
	}
	if (ft_strcmp(cmd_args[0], "export") == 0)
	{
		ft_export(cmd_args, mshell);
		return (mshell->exitcode);
	}
	return (FAIL); //no built-in matched
}


