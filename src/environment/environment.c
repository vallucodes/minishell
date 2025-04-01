
#include "../../inc/minishell.h"

static int init_env_storage(t_env *env, char **envp)
{
	int	var_amount;

	var_amount = 0;

	while (envp[var_amount])
		var_amount++;
	env->envp = malloc(sizeof(char *) * (var_amount + 1));
	if (!env->envp)
	{
		dprintf(2, "malloc error\n");
		return (FAIL);
	}
	env->allocated_capacity = var_amount + 1;
	env->len = 0;
	return (SUCCESS);
}

int copy_env(t_env *env, char **envp)
{
	int	i;

	if (init_env_storage(env, envp))
		return (FAIL);

	i = 0;
	while (envp[i])
	{
		env->envp[i] = ft_strdup(envp[i]);
		if(!env->envp[i])
		{
			dprintf(2, "malloc error\n");
			free_partial_env(env->envp, i); //rest not alloc yet so must not free all
			return (FAIL);
		}
		i++;
	}
	env->envp[i] = NULL;
	env->len = i;
	return (SUCCESS);
}
