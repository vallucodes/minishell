#include "../../inc/minishell.h"

int execute_builtin(t_minishell *mshell, char **cmd_args)
{
	if (!mshell || !cmd_args || !cmd_args[0])
	{
		ft_dprintf(2, "Giraffeshell: builtin execution error\n");
		mshell->exitcode = FAIL;
		return (mshell->exitcode);
	}
	if (ft_strncmp(cmd_args[0], "env", 4) == 0)
		return (ft_env(&mshell->envp, cmd_args));
	if (ft_strcmp(cmd_args[0], "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd_args[0], "echo") == 0)
			return (ft_echo(count_argv(cmd_args), cmd_args));
	if (ft_strcmp(cmd_args[0], "cd") == 0)
		return (ft_cd(&mshell->envp, count_argv(cmd_args), cmd_args));
	if (ft_strcmp(cmd_args[0], "exit") == 0)
	{
		ft_exit(cmd_args, mshell);
		return (mshell->exitcode);
	}
	if (ft_strcmp(cmd_args[0], "unset") == 0)
		return (ft_unset(cmd_args, mshell->envp));
	if (ft_strcmp(cmd_args[0], "export") == 0)
		return (ft_export(cmd_args, mshell->envp));
	return (FAIL);
}


