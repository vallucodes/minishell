
//#include "../../inc/minishell.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_env
{
	char			**envp;                // array of strings: "KEY=VALUE"
	unsigned int	allocated_capacity;   // how many total entries allocated
	unsigned int	len;                   // how many are actually used
}	t_env;

void free_env(t_env *env)
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

void free_partial_env(char **envp, int up_to)
{
	while (up_to--)
		free(envp[up_to]);
	free(envp);
}

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
		env->envp[i] = strdup(envp[i]); //change this
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

int main(int argc, char **argv, char **envp)
{
	t_env my_env;

	(void)argc;
	(void)argv;

	if (copy_env(&my_env, envp) != 0)
	{
		fprintf(stderr, "Failed to copy environment\n");
		return (1);
	}

	printf("Copied environment variables:\n");
	for (unsigned int i = 0; i < my_env.len; i++)
		printf("[%u] %s\n", i, my_env.envp[i]);

	free_env(&my_env);
	printf("\nEnvironment cleaned up.\n");

	return (0);
}

