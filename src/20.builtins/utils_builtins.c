#include "../../inc/minishell.h"

int count_argv(char **argv)
{
	int count = 0;
	while (argv && argv[count])
		count++;
	return count;
}

// is it a valid variable name for unset & export?
int	is_valid_identifier_range(const char *str, size_t len)
{
	size_t i = 0;

	if (!str || len == 0 || ft_isdigit(str[0]) || str[0] == '=')
		return (0);

	while (i < len)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	update_var_env(t_env *env, const char *arg, const char *key, int key_has_value)
{
	size_t i = 0;

	while (i < env->len)
	{
		if (match_env_key(env->envp[i], key))
		{
			if (key_has_value)
			{
				free(env->envp[i]);
				env->envp[i] = ft_strdup(arg);
				if (!env->envp[i])
					return (FAIL);
			}
			return (SUCCESS); // key found and updated
		}
		i++;
	}
	return (FAIL); // not found
}


int	add_var_to_env(t_env *env, const char *arg, const char *key, size_t key_len, int key_has_value)
{
	if (realloc_env_capacity(env) == FAIL)
		return (FAIL);

	if (key_has_value)
	{
		env->envp[env->len] = ft_strdup(arg);
		if (!env->envp[env->len])
			return (FAIL);
		env->len++;
	}
	else
	{
		char *new_var = malloc(key_len + 2);
		if (!new_var)
			return (FAIL);
		ft_memcpy(new_var, key, key_len);
		new_var[key_len] = '\0';
		env->envp[env->len++] = new_var;
	}
	env->envp[env->len] = NULL;
	return (SUCCESS);
}

