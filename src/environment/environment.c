#include "minishell.h"

int	copy_env(t_minishell *mshell, char **envp)
{

}



int init_minishell(t_minishell *mshell, char **envp)
{
	mshell->envp = copy_env("");
}
