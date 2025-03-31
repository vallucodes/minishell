
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
		perror("malloc:");
		return (1);
	}
	env->allocated_capacity = var_amount + 1;
	env->len = 0;
	return (0);
}

int copy_env(t_env *env, char **envp)
{
	int	i;

	if (init_env_storage(env, envp))
		return (1);

	i = 0;
	while (envp[i])
	{
		env->envp[i] = ft_strdup(envp[i]);
		if(!env->envp[i])
		{
			perror("malloc:");
			free_partial_env(env->envp, i); //rest not alloc yet so must not free all
			return (1);
		}
		i++;
	}
	env->envp[i] = NULL;
	env->len = i;
	return (0);
}





// int init_minishell(t_minishell *mshell, char **envp)
// {
// 	mshell->envp = copy_env("");
// }
