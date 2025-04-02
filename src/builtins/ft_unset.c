#include "../../inc/minishell.h"

int match_env_key(const char *env_entry, const char *key)
{
	size_t key_len = ft_strlen(key);
	return (ft_strncmp(env_entry, key, key_len) == 0 && env_entry[key_len] == '=');
}

void remove_env_var(t_env *env, const char *key)
{
	for (unsigned int i = 0; i < env->len; i++)
	{
		if (match_env_key(env->envp[i], key))
		{
			free(env->envp[i]);

			// Shift the remaining entries left
			for (unsigned int j = i; j < env->len - 1; j++)
				env->envp[j] = env->envp[j + 1];

			env->envp[env->len - 1] = NULL;
			env->len--;
			return;
		}
	}
}

int ft_unset(char **args, t_env *env)
{
	for (int i = 1; args[i]; i++)
	{
		if (is_valid_identifier(args[i]))
			remove_env_var(env, args[i]);
		else
			ft_dprintf(STDERR_FILENO, "minishell: unset: `%s': not a valid identifier\n", args[i]);
	}
	return (0);
}



int ft_unset(char **args, t_minishell *shell)
{

}
