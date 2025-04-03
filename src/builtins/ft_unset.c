#include "../../inc/minishell.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0] || ft_isdigit(str[0]) || str[0] == '=')
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int match_env_key(const char *env_entry, const char *key)
{
	int result;
	size_t key_len = ft_strlen(key);

	int match = ft_strncmp(env_entry, key, key_len);
	if (match == 0 && env_entry[key_len] == '=')
		return (1);
	else
		return (0);
}

static void	remove_env_var(t_env *env, const char *key)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < env->len)
	{
		if (match_env_key(env->envp[i], key))
		{
			free(env->envp[i]);
			j = i;
			while (j < env->len - 1)
			{
				env->envp[j] = env->envp[j + 1];
				j++;
			}
			env->envp[env->len - 1] = NULL;
			env->len--;
			return ;
		}
		i++;
	}
}

int	ft_unset(char **args, t_env *env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_valid_identifier(args[i]))
			remove_env_var(env, args[i]);
		else
			ft_dprintf(STDERR_FILENO, "minishell: unset: `%s': not a valid identifier\n", args[i]);
		i++;
	}
	return (0);
}

