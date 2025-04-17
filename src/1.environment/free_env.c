#include "../../inc/minishell.h"

void	exit_env(char *msg, t_env **env)
{
	perror(msg);
	if (env)
		free(*env);
	exit(FAIL);
}

void	free_env(t_env *env)
{
	unsigned int i;

	if (!env || !env->envp)
		return;

	i = 0;
	while (i < env->len)
	{
		free(env->envp[i]);
		i++;
	}
	free(env->envp);
	env->envp = NULL;
	env->len = 0;
	env->allocated_capacity = 0;
}

void	free_partial_env(char **envp, int up_to)
{
	while (up_to--)
		free(envp[up_to]);
	free(envp);
}
